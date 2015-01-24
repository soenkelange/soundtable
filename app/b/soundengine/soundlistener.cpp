#include "soundengine.h"

SoundListener::SoundListener(ISoundEngine* engine) :
    _position(vec3df(0,0,0))

{
      _engine = engine;
}

SoundListener::~SoundListener()
{

}

vec3df SoundListener::position() const
{
    return _position;
}

void SoundListener::setPosition(cv::Point3f position)
{
    _position = vec3df(position.x, position.y, position.z);
    _engine->setListenerPosition(_position, _lookDirection, _upVector);

}

vec3df SoundListener::lookDirection() const
{
    return _lookDirection;
}

void SoundListener::setLookDirection(cv::Point3f direction)
{
    _lookDirection = vec3df(direction.x, direction.y, direction.z);
    _engine->setListenerPosition(_position, _lookDirection, _upVector);
}

vec3df SoundListener::upVector() const
{
    return _upVector;
}

void SoundListener::setUpVector(cv::Point3f upVector)
{
    _upVector = vec3df(upVector.x, upVector.y, upVector.z);
    _engine->setListenerPosition(_position, _lookDirection, _upVector);
}


