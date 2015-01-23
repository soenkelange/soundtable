#include "cardsprocessor.h"

#include <vector>
#include <QDebug>

CardsProcessor::CardsProcessor()
{
    initDetectableCards();
}

CardsProcessor::~CardsProcessor()
{

}

void CardsProcessor::initDetectableCards() {
    std::vector<Card::Color> colors(3);
    colors[0] = Card::Yellow;
    colors[1] = Card::Blue;
    colors[2] = Card::Red;

    std::vector<Card::Shape> shapes(5);
    shapes[0] = Card::Triangle;
    shapes[1] = Card::Square;
    shapes[2] = Card::Hexagon;
    shapes[3] = Card::Circle;
    shapes[4] = Card::Star;

    for(unsigned long color = 0; color < colors.size(); color++) {
        for(unsigned long shape = 0; shape < shapes.size(); shape++) {
            Card card(colors[color], shapes[shape]);
            _detectableCards.append(card);
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
    cv::Mat processed;
    source.copyTo(processed);
    // Output every second
    if(_frameCounter >= _videoFormat.framesPerSecond()) {
        qDebug() << "Processing...";
        _frameCounter = 0;
    } else {
        _frameCounter++;
    }
    return processed;
}

QList<Card> CardsProcessor::getDetectableCards() const
{
    return _detectableCards;
}
