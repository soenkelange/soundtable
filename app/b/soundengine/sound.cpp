#include "sound.h"

Sound::Sound(const SoundSource &source) :
    _soundSorce(source),
    _volume(100),
    _position(cv::Point3f(0,0,0)),
    _looped(false),
    _minDistance(0),
    _maxDistance(100),
    _playbackSpeed(1)
{
}

Sound::~Sound()
{

}

SoundSource Sound::getSoundSource() const
{
    return _soundSorce;
}

float Sound::volume() const
{
    return _volume;
}

void Sound::setVolume(float volume)
{
    _volume = volume;
}

cv::Point3f Sound::position() const
{
    return _position;
}

void Sound::setPosition(cv::Point3f position)
{
    _position = position;
}

bool Sound::isLooped() const
{
    return _looped;
}

void Sound::setIsLooped(bool looped)
{
    _looped = looped;
}

float Sound::minDistance() const
{
    return _minDistance;
}

void Sound::setMinDistance(float min)
{
    _minDistance = min;
}

float Sound::maxDistance() const
{
    return _maxDistance;
}

void Sound::setMaxDistance(float max)
{
    _maxDistance = max;
}

float Sound::playbackSpeed() const
{
    return _playbackSpeed;
}

void Sound::setPlaybackSpeed(float speed)
{
    _playbackSpeed = speed;
}
