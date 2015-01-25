#include "sound.h"

Sound::Sound(irrklang::ISound *sound) :
    _sound(sound)
{
}

Sound::~Sound()
{

}

float Sound::volume() const
{
    return _sound->getVolume();
}

void Sound::setVolume(float volume)
{
    _sound->setVolume(volume);
}

irrklang::vec3df Sound::position() const
{
    return _sound->getPosition();
}

void Sound::setPosition(irrklang::vec3df position)
{
    _sound->setPosition(position);
}

bool Sound::isLooped() const
{
    return _sound->isLooped();
}

void Sound::setIsLooped(bool looped)
{
    _sound->setIsLooped(looped);
}

float Sound::minDistance() const
{
    return _sound->getMinDistance();
}

void Sound::setMinDistance(float min)
{
    _sound->setMinDistance(min);
}

float Sound::playbackSpeed() const
{
    return _sound->getPlaybackSpeed();
}

void Sound::setPlaybackSpeed(float speed)
{
    _sound->setPlaybackSpeed(speed);
}

void Sound::stop()
{
    _sound->stop();
}

void Sound::drop()
{
    _sound->drop();
}
