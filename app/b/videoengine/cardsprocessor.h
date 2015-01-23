#ifndef CARDSPROCESSOR_H
#define CARDSPROCESSOR_H

#include "videoprocessor.h"
#include "card.h"

class CardsProcessor : public VideoProcessor
{
public:
    CardsProcessor();
    ~CardsProcessor();

    void initDetectableCards();

    void startProcessing(const VideoFormat &format);
    cv::Mat process(const cv::Mat &source);

    QList<Card> getDetectableCards() const;

private:
    VideoFormat _videoFormat;
    int _frameCounter;
    QList<Card> _detectableCards;

};

#endif // CARDSPROCESSOR_H
