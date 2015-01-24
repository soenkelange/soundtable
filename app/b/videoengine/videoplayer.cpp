#include "videoplayer.h"

#include <QDebug>

VideoPlayer::VideoPlayer(QObject *parent) :
    QObject(parent),
    _videoEngine(new VideoEngine),
    _state(Stopped)
{

}

VideoPlayer::~VideoPlayer()
{
    stop();
    delete _videoEngine;
}

bool VideoPlayer::setInput(QString filePath)
{
    _videoEngine->openFile(filePath);
    return true;
}

bool VideoPlayer::setInput(int cameraDevice)
{
    _videoEngine->openCamera(cameraDevice);
    return true;
}

void VideoPlayer::setInputVideoWidget(VideoWidget *widget)
{
    qDebug() << "VideoPlayer::setInputVideoWidget";
    connect(_videoEngine, SIGNAL(sendInputImage(const QImage&)), widget, SLOT(setImage(const QImage&)));
}

void VideoPlayer::setOutputVideoWidget(VideoWidget *widget)
{
    connect(_videoEngine, SIGNAL(sendProcessedImage(const QImage&)), widget, SLOT(setImage(const QImage&)));
}

VideoPlayer::State VideoPlayer::state() const
{
    return _state;
}

void VideoPlayer::changeState(VideoPlayer::State newState)
{
    if (newState != _state) {
        switch(newState) {
        case VideoPlayer::Stopped:
            _videoEngine->stop();
            break;
        case VideoPlayer::Playing:
            _videoEngine->start();
            break;
        default:
            qDebug() << "Unhandled state in VideoPlayer::changeState";
            return;
        }
        _state = newState;
        emit stateChanged(_state);
    }
}

void VideoPlayer::play()
{
    qDebug() << "VideoPlayer::play()";
    changeState(VideoPlayer::Playing);
}

void VideoPlayer::stop()
{
    qDebug() << "VideoPlayer::stop()";
    changeState(VideoPlayer::Stopped);
}

