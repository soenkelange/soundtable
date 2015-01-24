#include "sound.h"

Sound::Sound(const SoundSource &source):

    _soundSorce(source),
    _volume(1),
    _position(vec3df(0,0,0)),
    _looped(false),
    _minDistance(0),
    _maxDistance(100),
    _playbackSpeed(1)
{
}

Sound::~Sound()
{

}
void Sound::setSound(ISound* sound)
{
     _sound = sound;
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
    if(volume > 1)
    {
        volume = 1;
    }else if(volume < 0)
    {
        volume = 0;
    }
    _volume = volume;
    _sound->setVolume(_volume);

}

vec3df Sound::position() const
{
    return _position;
}

void Sound::setPosition(cv::Point3f position)
{
    _position = vec3df(position.x, position.y, position.z);

    _sound->setPosition(_position);
}

bool Sound::isLooped() const
{
    return _looped;
}

void Sound::setIsLooped(bool looped)
{
    _looped = looped;
    _sound->setIsLooped(_looped);
}

float Sound::minDistance() const
{
    return _minDistance;
}

void Sound::setMinDistance(float min)
{
    _minDistance = min;
    _sound->setMinDistance(_minDistance);
}

float Sound::maxDistance() const
{
    return _maxDistance;
}

void Sound::setMaxDistance(float max)
{
    _maxDistance = max;
    _sound->setMaxDistance(_maxDistance);
}

float Sound::playbackSpeed() const
{
    return _playbackSpeed;
}

void Sound::setPlaybackSpeed(float speed)
{
    _playbackSpeed = speed;
    _sound->setPlaybackSpeed(_playbackSpeed);
}

void Sound::stopSound()
{
    _sound->stop();
}

void Sound::dropSound()
{
    _sound->drop();
}
