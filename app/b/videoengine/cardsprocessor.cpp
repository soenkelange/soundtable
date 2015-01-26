#include "cardsprocessor.h"

#include <vector>
#include <cmath>
#include <QDebug>

CardsProcessor::CardsProcessor() :
    _output(CardsProcessor::Original),
    _threshold(1000),
    _cannyLowerThreshold(100),
    _cannyUpperThreshold(300),
    _cannyGradient(false),
    _colorKeyingOptions(3)
{
    initColorKeyingOption();
    initDetectableCards();
}

CardsProcessor::~CardsProcessor()
{

}

void CardsProcessor::initDetectableCards() {
    std::vector<Card::Color> colors(3);
    colors[0] = Card::Yellow;
    colors[1] = Card::Red;
    colors[2] = Card::Blue;

    std::vector<Card::Shape> shapes(5);
    shapes[0] = Card::Triangle;
    shapes[1] = Card::Square;
    shapes[2] = Card::Hexagon;
    shapes[3] = Card::Circle;
    shapes[4] = Card::Star;

    for(unsigned long color = 0; color < colors.size(); color++) {
        for(unsigned long shape = 0; shape < shapes.size(); shape++) {
            Card *card = new Card(colors[color], shapes[shape]);
            _detectableCards.push_back(card);
        }
    }
}

void CardsProcessor::startProcessing(const VideoFormat &format)
{
    qDebug() << "Start processing...";
    _videoFormat = format;
    _frameCounter = 0;
}

cv::Mat CardsProcessor::process(const cv::Mat &source)
{
    // Set all cards detected = false;
    for(int i = 0; i < _detectableCards.size(); i++) {
        Card *card = _detectableCards.at(i);
        card->setDetected(false);
    }

    cv::Mat traceview = cv::Mat::zeros(source.size(), CV_8UC3);
    cv::Mat blueBinary = processColor(source, CardsProcessor::Blue, traceview);
    cv::Mat yellowBinary = processColor(source, CardsProcessor::Yellow, traceview);
    cv::Mat redBinary = processColor(source, CardsProcessor::Red, traceview);

    // Set all undetected cards to visible = false;
    for(int i = 0; i < _detectableCards.size(); i++) {
        Card *card = _detectableCards.at(i);
        if(!card->isDetected()) {
            card->setVisibility(false);
        }
    }
    switch(_output) {
    case CardsProcessor::BlueBinary:
        return blueBinary;
    case CardsProcessor::YellowBinary:
        return yellowBinary;
    case CardsProcessor::RedBinary:
        return redBinary;
    case CardsProcessor::Traceview:
        return traceview;
    default:
        return source;
    }
}

cv::Mat CardsProcessor::processColor(const cv::Mat &source, CardsProcessor::CK_Color ckColor, cv::Mat &traceview)
{
    cv::Mat colorBinary = applyColorKeying(source, ckColor);
    cv::Mat binary;
    colorBinary.copyTo(binary);

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0,0));

    std::vector<bool> checked(contours.size(), false);
    for(int i = 0; i < contours.size(); i++) {
        if (checked[i]) {
            continue;
        }
        if (hierarchy[i][2] == -1 || hierarchy[i][3] != -1) {
            continue;
        }
        if (cv::contourArea(contours[i]) < 25000) {
            continue;
        }

        std::vector<int> childs;
        findChilds(i, hierarchy, childs, checked);
        int largestArea = 0;
        int largestAreaIdx = 0;
        std::vector<int> usefulContours;
        for(int j = 0; j < childs.size(); j++) {
            int childIdx = childs[j];
            double contourArea = cv::contourArea(contours[childIdx]);
            if (contourArea < 1000) {
                continue;
            }
            std::vector<cv::Point> contour = contours[childIdx];
            usefulContours.push_back(childIdx);
            if (contourArea > largestArea) {
                largestAreaIdx = childIdx;
                largestArea = contourArea;
            }
            if(_output == CardsProcessor::Traceview) {
                std::vector<cv::Point> approxPoly;
                cv::approxPolyDP(contours[childIdx], approxPoly, 3, true);
                cv::RotatedRect rect = cv::minAreaRect(approxPoly);
                drawRotatedRect(traceview, rect, cv::Scalar(0,255,0));
                drawCross(traceview, rect.center, cv::Scalar(0,255,0));
            }
        }

        // Find Shape
        std::vector<cv::Point> shapePoly;
        cv::approxPolyDP(
                    cv::Mat(contours[largestAreaIdx]),
                    shapePoly,
                    cv::arcLength(cv::Mat(contours[largestAreaIdx]), true) * 0.02,
                    true);
        int shape = findShape(contours[largestAreaIdx], shapePoly);
        if (shape == -1) {
            continue;
        }
        // Find rotation
        std::vector<std::vector<cv::Point> > markers;
        for(int j = 0; j < usefulContours.size(); j++) {
            if (usefulContours[j] != largestAreaIdx) {
                markers.push_back(contours[usefulContours[j]]);
            }
        }
        float rotation = findRotation(markers);

        std::vector<cv::Point> approxPoly;
        cv::approxPolyDP(contours[i], approxPoly, 3, true);
        cv::RotatedRect rect = cv::minAreaRect(approxPoly);
        Card *card = getCard(processorToCardColor(ckColor), shape);
        card->setPosition(rect.center);
        card->setRotation(rotation);
        card->setVisibility(true);
        card->setDetected(true);

        if(_output == CardsProcessor::Traceview) {
            drawRotatedRect(traceview, rect, card->colorAsScalar());
            drawCross(traceview, card->position(), cv::Scalar(0,255,0));
            cv::putText(traceview, card->shapeName().toStdString() + " " + QString::number(card->rotation()).toStdString(), card->position(), cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(255,255,255), 2);
        }
    }

    updateFrameCounter();
    return colorBinary;
}


/*
 * See http://opencv-code.com/tutorials/detecting-simple-shapes-in-an-image/
 */
int CardsProcessor::findShape(const std::vector<cv::Point> &contour, const std::vector<cv::Point> &approxPoly)
{
    if(approxPoly.size() == 3) {
        return Card::Triangle;
    } else if (approxPoly.size() >= 4 && approxPoly.size() <= 9) {
        int size = approxPoly.size();
        std::vector<double> cos;
        for(int i = 2; i < size; i++) {
            cos.push_back(angle(approxPoly[i % size], approxPoly[i - 2], approxPoly[i - 1]));
        }
        std::sort(cos.begin(), cos.end());

        double minCos = cos.front();
        double maxCos = cos.back();
        if (size >= 4 && size <= 5 && minCos >= -0.3 && maxCos <= 0.5) {
            return Card::Square;
        } else if (size >= 6 && size <= 9) {
            return Card::Hexagon;
        }
    } else if (approxPoly.size() >= 10 && approxPoly.size() <= 11) {
        return Card::Star;
    }
    else {
        double area = cv::contourArea(contour);
        cv::Rect rect = cv::boundingRect(contour);
        int radius = rect.width / 2;
        if (std::abs(1 - ((double)rect.width / rect.height)) <= 0.2 &&
                std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2)
        {
            return Card::Circle;
        }
    }
    return -1;
}

float CardsProcessor::findRotation(const std::vector<std::vector<cv::Point> > &markers)
{

    if (markers.size() == 3) {

        const cv::Point2f a = cv::minAreaRect(markers[0]).center;
        const cv::Point2f b = cv::minAreaRect(markers[1]).center;
        const cv::Point2f c = cv::minAreaRect(markers[2]).center;
        float ab = distance(a,b);
        float ac = distance(a,c);
        float bc = distance(b,c);
        cv::Point2f cornerPoint;

        cv::Point2f p1(0,1);
        cv::Point2f p2;
        if (ab > bc && ab > ac) {
            p2 = a-b;
        } else if (ac > ab && ac > bc) {
            p2 = a-c;
        } else if(bc > ab && bc > ac) {
            p2 = b-c;
        }
        return angle(p1,p2);

    }
    return -1;
}

void CardsProcessor::findChilds(int contourIndex, const std::vector<cv::Vec4i> &hierarchy, std::vector<int> &childs, std::vector<bool> &checked)
{
    if(hierarchy[contourIndex][2] == -1) {
        return;
    }
    int childIdx = hierarchy[contourIndex][2];
    findChilds(childIdx, hierarchy, childs, checked);
    childs.push_back(childIdx);
    checked[childIdx];
    while(hierarchy[childIdx][0] != -1) {
        childIdx = hierarchy[childIdx][0];
        findChilds(childIdx, hierarchy, childs, checked);
        childs.push_back(childIdx);
        checked[childIdx];
    }
}

cv::Mat CardsProcessor::applyCannyEdgeDetection(const cv::Mat &grayscale)
{
    cv::Mat cannyOutput;
    cv::blur(grayscale, cannyOutput, cv::Size(3,3));
    cv::Canny(cannyOutput, cannyOutput, _cannyLowerThreshold, _cannyUpperThreshold, 3, _cannyGradient);
    return cannyOutput;
}

cv::Mat CardsProcessor::applyColorKeying(const cv::Mat &rgb, CardsProcessor::CK_Color color)
{
    cv::Mat hsv;
    cv::cvtColor(rgb, hsv, cv::COLOR_BGR2HSV);

    cv::Mat binary;
    cv::inRange(hsv,_colorKeyingOptions[color][CardsProcessor::Lower],
            _colorKeyingOptions[color][CardsProcessor::Upper],
            binary);

    cv::erode(binary, binary, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));
    cv::dilate(binary, binary, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));

    cv::erode(binary, binary, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));
    cv::dilate(binary, binary, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));

    return binary;
}

Card* CardsProcessor::getCard(Card::Color color, int shape)
{
    // TODO: Poor solution, find a better way
    Card::Shape cardShape;
    switch(shape) {
    case Card::Triangle:
        cardShape = Card::Triangle;
        break;
    case Card::Square:
        cardShape = Card::Square;
        break;
    case Card::Hexagon:
        cardShape = Card::Hexagon;
        break;
    case Card::Circle:
        cardShape = Card::Circle;
        break;
    case Card::Star:
        cardShape = Card::Star;
        break;
    }
    for(int i = 0; i <= _detectableCards.size(); i++) {
        Card *card = _detectableCards[i];
        if (card->color() == color && card->shape() == cardShape) {
            return card;
        }
    }
}

Card::Color CardsProcessor::processorToCardColor(CardsProcessor::CK_Color color)
{
    switch(color) {
    case CardsProcessor::Yellow:
        return Card::Yellow;
    case CardsProcessor::Red:
        return Card::Red;
    case CardsProcessor::Blue:
        return Card::Blue;
    default:
        qDebug() << "CardsProcessor::processorToCardColor(): Unhandled case in switch method";
    }
}

void CardsProcessor::updateFrameCounter()
{
    // Reset every second
    if (_frameCounter >= _videoFormat.framesPerSecond()) {
        _frameCounter = 0;
    } else {
        _frameCounter++;
    }
}

void CardsProcessor::debugOutput(QString output)
{
    if (_frameCounter >= 30) {
        qDebug() << output;
    }
}

std::vector<Card *> CardsProcessor::getDetectableCards() const
{
    return _detectableCards;
}

CardsProcessor::Output CardsProcessor::output() const
{
    return _output;
}

void CardsProcessor::setOutput(int output)
{
    qDebug() << "output" << output;
    switch(output) {
    case CardsProcessor::BlueBinary:
        _output = CardsProcessor::BlueBinary;
        break;
    case CardsProcessor::YellowBinary:
        _output = CardsProcessor::YellowBinary;
        break;
    case CardsProcessor::RedBinary:
        _output = CardsProcessor::RedBinary;
        break;
    case CardsProcessor::Traceview:
        _output = CardsProcessor::Traceview;
        break;
    case CardsProcessor::Original:
        _output = CardsProcessor::Original;
        break;
    default:
        qDebug() << "CardsProcessor::setOutput - Unhandled case";
    }
}

int CardsProcessor::threshold() const
{
    return _threshold;
}

void CardsProcessor::setThreshold(int threshold)
{
    qDebug() << "Threshold: " << QString::number(threshold);
    _threshold = threshold;
}

int CardsProcessor::cannyLowerThreshold() const
{
    return _cannyLowerThreshold;
}

void CardsProcessor::setCannyLowerThreshold(int threshold)
{
    _cannyLowerThreshold = threshold;
}

int CardsProcessor::cannyUpperThreshold() const
{
    return _cannyUpperThreshold;
}

void CardsProcessor::setCannyUpperThreshold(int threshold)
{
    _cannyUpperThreshold = threshold;
}

bool CardsProcessor::cannyGradient() const
{
    return _cannyGradient;
}

void CardsProcessor::setCannyGradient(bool gradient)
{
    qDebug() << "Gradient:" << gradient;
    _cannyGradient = gradient;
}

void CardsProcessor::initColorKeyingOption()
{
    qDebug() << "Init ColorKeying options..";
    cv::Scalar yellowLower = cv::Scalar(0,78,183);
    cv::Scalar yellowUpper = cv::Scalar(20,148,255);
    cv::Scalar redLower = cv::Scalar(132,114,152);
    cv::Scalar redUpper = cv::Scalar(179,228,245);
    cv::Scalar blueLower = cv::Scalar(95, 114, 146);
    cv::Scalar blueUpper = cv::Scalar(108,238,255);

    std::vector<cv::Scalar> yellowRanges(2);
    yellowRanges[CardsProcessor::Lower] = yellowLower;
    yellowRanges[CardsProcessor::Upper] = yellowUpper;

    std::vector<cv::Scalar> redRanges(2);
    redRanges[CardsProcessor::Lower] = redLower;
    redRanges[CardsProcessor::Upper] = redUpper;

    std::vector<cv::Scalar> blueRanges(2);
    blueRanges[CardsProcessor::Lower] = blueLower;
    blueRanges[CardsProcessor::Upper] = blueUpper;

    _colorKeyingOptions[CardsProcessor::Yellow] = yellowRanges;
    _colorKeyingOptions[CardsProcessor::Red] = redRanges;
    _colorKeyingOptions[CardsProcessor::Blue] = blueRanges;
}

int CardsProcessor::getColorKeyingOption(CardsProcessor::CK_Color color,
                                          CardsProcessor::CK_Range range,
                                          CardsProcessor::CK_HSV hsv)
{
    /* DEBUG BEGIN
    QString rangeName;
    switch(range) {
    case CardsProcessor::Lower:
        rangeName = "Lower";
        break;
    case CardsProcessor::Upper:
        rangeName = "Upper";
        break;
    default:
        rangeName = "Invalid range";
    }

    QString hsvName;
    switch(hsv) {
    case CardsProcessor::Hue:
        hsvName = "Hue";
        break;
    case CardsProcessor::Saturation:
        hsvName = "Saturation";
        break;
    case CardsProcessor::Value:
        hsvName = "Value";
        break;
    default:
        hsvName = "Invalid hsv value";
    }

    QString colorName;
    switch(color) {
    case CardsProcessor::Yellow:
        colorName = "Yellow";
        break;
    case CardsProcessor::Red:
        colorName = "Red";
        break;
    case CardsProcessor::Blue:
        colorName = "Blue";
        break;
    default:
        colorName = "Invalid color";
    }
    qDebug() << "Getting " << rangeName << "("<< QString::number(range)  << ")"
             << " " << hsvName << "("<< QString::number(hsv)  << ")"
             << " of color " << colorName << "("<< QString::number(color)  << ")";
    DEBUG END */

    return _colorKeyingOptions[color][range].val[hsv];
}

void CardsProcessor::setColorKeyingOption(CardsProcessor::CK_Color color,
                                          CardsProcessor::CK_Range range,
                                          CardsProcessor::CK_HSV hsv,
                                          int value)
{
    /* DEBUG BEGIN
    QString rangeName;
    switch(range) {
    case CardsProcessor::Lower:
        rangeName = "Lower";
        break;
    case CardsProcessor::Upper:
        rangeName = "Upper";
        break;
    default:
        rangeName = "Invalid range";
    }

    QString hsvName;
    switch(hsv) {
    case CardsProcessor::Hue:
        hsvName = "Hue";
        break;
    case CardsProcessor::Saturation:
        hsvName = "Saturation";
        break;
    case CardsProcessor::Value:
        hsvName = "Value";
        break;
    default:
        hsvName = "Invalid hsv value";
    }

    QString colorName;
    switch(color) {
    case CardsProcessor::Yellow:
        colorName = "Yellow";
        break;
    case CardsProcessor::Red:
        colorName = "Red";
        break;
    case CardsProcessor::Blue:
        colorName = "Blue";
        break;
    default:
        colorName = "Invalid color";
    }
    qDebug() << "Setting " << rangeName << "("<< QString::number(range)  << ")"
             << " " << hsvName << "("<< QString::number(hsv)  << ")"
             << " of color " << colorName << "("<< QString::number(color)  << ")"
             << " to " << value;
    DEBUG END */

    _colorKeyingOptions[color][range].val[hsv] = value;
}

float CardsProcessor::distance(cv::Point2f p1, cv::Point2f p2)
{
    return sqrt( pow( abs(p1.x - p2.x), 2) + abs(p1.y - p2.y));
}

double CardsProcessor::angle(cv::Point p1, cv::Point p2, cv::Point p3)
{
    double dx1 = p1.x - p3.x;
    double dy1 = p1.y - p3.y;
    double dx2 = p2.x - p3.x;
    double dy2 = p2.y - p3.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

float CardsProcessor::angle(cv::Point p1, cv::Point p2)
{
    /*float a = (p1.x * p2.x) + (p1.y * p2.y);
    float b = sqrt(pow(p1.x,2) + pow(p1.y,2));
    float c = sqrt(pow(p2.x,2) + pow(p2.y,2));
    return acos(a/(b*c));*/
    float len1 = sqrt(p1.x * p1.x + p1.y * p1.y);
    float len2 = sqrt(p2.x * p2.x + p2.y * p2.y);

    float dot = p1.x * p2.x + p1.y * p2.y;

    float a = dot / (len1 * len2);

    if (a >= 1.0)
        return 0.0;
    else if (a <= -1.0)
        return M_PI;
    else
        return acos(a); // 0..PI
}

void CardsProcessor::drawConnectedLine(cv::Mat &output, const std::vector<cv::Point> &points, const cv::Scalar &color)
{

    for(int j = 0; j < points.size(); j++) {
        int point = j + 1;
        if (point == points.size()) {
            point = 0;
        }
        cv::line(output, points[j], points[point], color, 2);
    }
}

void CardsProcessor::drawRotatedRect(cv::Mat &output, const cv::RotatedRect &rect, const cv::Scalar &color)
{
    cv::Point2f rectPoints[4];
    rect.points(rectPoints);
    for( int j = 0; j < 4; j++ ) {
        cv::line(output, rectPoints[j], rectPoints[(j+1)%4], color, 2);
    }
}

void CardsProcessor::drawCross(cv::Mat &output, const cv::Point &point, cv::Scalar color, int length) {
    if(point.x > 0 && point.y > 0) {
        line(output, point - cv::Point(0, length), point + cv::Point(0,length), color, 2);
        line(output, point - cv::Point(length, 0), point + cv::Point(length, 0), color, 2);
    }
}


//cv::cvtColor(source, grayscale, cv::COLOR_BGR2GRAY);




// Canny edge detection
//    cv::Mat grayscale;
//    cv::cvtColor(source, grayscale, cv::COLOR_BGR2GRAY);
//    cv::Mat binary = applyCannyEdgeDetection(grayscale);

//    // Find Contours
//    std::vector<std::vector<cv::Point> > contours;
//    std::vector<cv::Vec4i> hierarchy;
//    findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0,0));

//    // Draw contours
//    cv::Mat drawing = cv::Mat::zeros(binary.size(), CV_8UC3);
//    cv::RNG rng(12345);

//    std::vector<std::vector<cv::Point> > contourPolys(contours.size());
//    std::vector<cv::Rect> boundingRects(contours.size());

//    for(int i = 0; i < contours.size(); i++) {
//        std::vector<cv::Point> approxPoly;
//        cv::approxPolyDP(contours[i], approxPoly, 3, true);
//        cv::Rect rect = cv::boundingRect(cv::Mat(approxPoly));

//        cv::drawContours(drawing, contours, i, cv::Scalar(255,255,255), -1, 8, hierarchy, 0, cv::Point());
//        cv::rectangle(drawing, rect.tl(), rect.br(), cv::Scalar(0,0,255), 2, 8, 0);
//    }

/*cv::Mat binaryBlue = applyColorKeying(source, CardsProcessor::Blue);
cv::Mat binaryYellow= applyColorKeying(source, CardsProcessor::Yellow);
cv::Mat binaryRed= applyColorKeying(source, CardsProcessor::Red);
cv::Mat binary;
cv::bitwise_or(binaryBlue, binaryYellow, binary);
cv::bitwise_or(binary, binaryRed, binary);*/

/*std::vector<std::vector<cv::Point> > contours;
std::vector<cv::Vec4i> hierarchy;
cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0,0));*/


/*//cv::Mat drawing = cv::Mat::zeros(binary.size(), CV_8UC3);
cv::Mat drawing;
source.copyTo(drawing);
debugOutput("Number of countours: " + QString::number(contours.size()));
int numberOfDrawnContours = 0;
for(int i = 0; i < contours.size(); i++) {
    int area = cv::contourArea(contours[i]);
    if(area < 300) {
        continue;
    }


    std::vector<cv::Point> approxPoly;
    cv::approxPolyDP(contours[i], approxPoly, 3, true);
    if (approxPoly.size() == 6) {
        debugOutput("Hexagon");
    }


    cv::Rect rect = cv::boundingRect(cv::Mat(approxPoly));
    //cv::drawContours(drawing, contours, i, cv::Scalar(255,255,255), -1, 8, hierarchy, 0, cv::Point());
    cv::rectangle(drawing, rect.tl(), rect.br(), cv::Scalar(0,0,255), 2, 8, 0);
    numberOfDrawnContours++;
}
debugOutput("Number of drawn countours: " + QString::number(numberOfDrawnContours));
updateFrameCounter();
return drawing;*/

// Draw hierarchies

/*cv::Mat drawing;
source.copyTo(drawing);
for(int i = 0; i < contours.size(); i++) {
    if (hierarchy[i][2] == -1) {
        continue;
    }
    int cardRectangle = i;
    cv::drawContours(drawing, contours, cardRectangle, cv::Scalar(255,255,255), -1, 8, hierarchy, 0, cv::Point());
    // Firstchild
    int child = hierarchy[i][2];
    while(hierarchy[child][0] != -1) {
        if (cv::contourArea(contours[child]) > 100) {
            std::vector<cv::Point> approxPoly;
            cv::approxPolyDP(contours[child], approxPoly, 3, true);
            cv::drawContours(drawing, contours, child, cv::Scalar(0,0,255), -1, 8, hierarchy, 0, cv::Point());
        }
        //cv::drawContours(drawing, contours, child, cv::Scalar(0,0,255), -1, 8, hierarchy, 0, cv::Point());
        child++;
    }

    //cv::drawContours(drawing, contours, child, cv::Scalar(0,0,255), -1, 8, hierarchy, 0, cv::Point());
}*/

