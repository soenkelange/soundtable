#include "soundlistener.h"

SoundListener::SoundListener(SoundListenerEventListener *listener) :
    _position(irrklang::vec3df(0,0,0)),
    _lookDirection(1,0,0),
    _listener(listener),
    _upVector(0,0,1)
{
}

SoundListener::~SoundListener()
{
}

irrklang::vec3df SoundListener::position() const
{
    return _position;
}

void SoundListener::setPosition(irrklang::vec3df position)
{
    if (position != _position) {
        _position = position;
        _listener->positionChanged();
    }
}

irrklang::vec3df SoundListener::lookDirection() const
{
    return _lookDirection;
}

void SoundListener::setLookDirection(irrklang::vec3df direction)
{
    if (direction != _lookDirection) {
        _lookDirection = direction;
        _listener->lookDirectionChanged();
    }
}

irrklang::vec3df SoundListener::upVector() const
{
    return _upVector;
}

void SoundListener::setUpVector(irrklang::vec3df upVector)
{
    if (upVector!= _upVector) {
        _upVector = upVector;
        _listener->upVectorChanged();
    }
}


