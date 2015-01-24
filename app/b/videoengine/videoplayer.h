#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include "videoengine.h"
#include "videowidget.h"
#include "videoprocessor.h"

class VideoPlayer : public QObject
{
    Q_OBJECT
public:
    enum State {
        Stopped,
        Playing
    };

    explicit VideoPlayer(QObject *parent = 0);
    ~VideoPlayer();

    bool setInput(QString filePath);
    bool setInput(int cameraDevice);
    void setInputVideoWidget(VideoWidget *widget);
    void setOutputVideoWidget(VideoWidget *widget);
    void setVideoProcessor(VideoProcessor *processor);

    VideoPlayer::State state() const;

private:
    void changeState(VideoPlayer::State newState);

signals:
    void stateChanged(VideoPlayer::State newState);

public slots:
    void play();
    void stop();

private:
    VideoEngine *_videoEngine;
    State _state;

};

#endif // VIDEOPLAYER_H
