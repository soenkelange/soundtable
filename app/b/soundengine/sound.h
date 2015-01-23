#ifndef SOUND_H
#define SOUND_H
#include <irrKlang.h>
#include "soundsource.h"
#include <opencv2/opencv.hpp>

using namespace irrklang;
class Sound
{
public:
    Sound(const SoundSource &source);
    ~Sound();

    SoundSource getSoundSource() const;
    float volume() const;
    void setVolume(float volume);
    cv::Point3f position() const;
    void setPosition(cv::Point3f position);
    bool isLooped() const;
    void setIsLooped(bool looped);
    float minDistance() const;
    void setMinDistance(float min);
    float maxDistance() const;
    void setMaxDistance(float max);
    float playbackSpeed() const;
    void setPlaybackSpeed(float speed);
    void setSound(ISound* sound);

private:
    ISound* _sound;
    SoundSource _soundSorce;
    float _volume;
    cv::Point3f _position;
    bool _looped;
    float _minDistance;
    float _maxDistance;
    float _playbackSpeed;
};

#endif // SOUND_H
