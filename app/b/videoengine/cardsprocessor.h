#ifndef CARDSPROCESSOR_H
#define CARDSPROCESSOR_H

#include <QObject>
#include "videoprocessor.h"
#include "card.h"

class CardsProcessor : public QObject, public VideoProcessor
{
    Q_OBJECT

public:
    enum Output {
        Original,
        Traceview,
        BlueBinary,
        RedBinary,
        YellowBinary,
    };

    enum CK_Color {
        Yellow = 0,
        Red = 1,
        Blue = 2,
    };

    enum CK_Range {
        Lower = 0,
        Upper = 1,
    };

    enum CK_HSV {
        Hue = 0,
        Saturation = 1,
        Value = 2,
    };

    CardsProcessor();
    ~CardsProcessor();

    void startProcessing(const VideoFormat &format);
    cv::Mat process(const cv::Mat &source);
    cv::Mat processColor(const cv::Mat &source, CardsProcessor::CK_Color color, cv::Mat &traceview);

    int findShape(const std::vector<cv::Point> &contour, const std::vector<cv::Point> &approxPoly);
    float findRotation(const std::vector<std::vector<cv::Point> > &markers);
    void findChilds(int contourIndex,
                    const std::vector<cv::Vec4i> &hierarchy,
                    std::vector<int> &childs,
                    std::vector<bool> &checked);

    QList<Card> getDetectableCards() const;


    CardsProcessor::Output output() const;
    int threshold() const;
    int cannyLowerThreshold() const;
    int cannyUpperThreshold() const;
    bool cannyGradient() const;

    int getColorKeyingOption(CardsProcessor::CK_Color color,
                             CardsProcessor::CK_Range range,
                             CardsProcessor::CK_HSV hsv);
    void setColorKeyingOption(CardsProcessor::CK_Color color,
                              CardsProcessor::CK_Range range,
                              CardsProcessor::CK_HSV hsv,
                              int value);

    float distance(cv::Point2f p1, cv::Point2f p2);
    double angle(cv::Point p1, cv::Point p2, cv::Point p3);
    float angle(cv::Point p1, cv::Point p2);
    void drawConnectedLine(cv::Mat &output, const std::vector<cv::Point> &points, const cv::Scalar &color);
    void drawRotatedRect(cv::Mat &output, const cv::RotatedRect &rect, const cv::Scalar &color);
    void drawCross(cv::Mat &output, const cv::Point &point, cv::Scalar color,  int length = 10);

protected:
    void initDetectableCards();
    void initColorKeyingOption();

    cv::Mat applyCannyEdgeDetection(const cv::Mat &grayscale);
    cv::Mat applyColorKeying(const cv::Mat &rgb, CardsProcessor::CK_Color color);

    Card getCard(Card::Color color, int shape);
    Card::Color processorToCardColor(CardsProcessor::CK_Color color);
    void updateFrameCounter();
    void debugOutput(QString output);

public slots:
    void setOutput(int output);
    void setThreshold(int threshold);
    void setCannyLowerThreshold(int threshold);
    void setCannyUpperThreshold(int threshold);
    void setCannyGradient(bool gradient);

private:
    VideoFormat _videoFormat;
    int _frameCounter;
    CardsProcessor::Output _output;
    QList<Card> _detectableCards;

    // Settings
    int _threshold;

    // Canny Settings
    int _cannyLowerThreshold;
    int _cannyUpperThreshold;
    bool _cannyGradient;

    // Color Keying Settings
    std::vector<std::vector<cv::Scalar> > _colorKeyingOptions;

};

#endif // CARDSPROCESSOR_H
