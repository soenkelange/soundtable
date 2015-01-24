#include "soundlistener.h"

SoundListener::SoundListener() :
    _position()
{

}

SoundListener::~SoundListener()
{

}

cv::Point3f SoundListener::position() const
{
    return _position;
}

void SoundListener::setPosition(cv::Point3f position)
{
    _position = position;
    _engine->setListenerPosition(_position, _lookDirection, _upVector);

}

cv::Point3f SoundListener::lookDirection() const
{
    return _lookDirection;
}

void SoundListener::setLookDirection(cv::Point3f direction)
{
    _lookDirection = direction;
    _engine->setListenerPosition(_position, _lookDirection, _upVector);
}

cv::Point3f SoundListener::upVector() const
{
    return _upVector;
}

void SoundListener::setUpVector(cv::Point3f upVector)
{
    _upVector = upVector;
    _engine->setListenerPosition(_position, _lookDirection, _upVector);
}


