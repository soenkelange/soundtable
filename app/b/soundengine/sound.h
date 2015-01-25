#ifndef SOUND_H
#define SOUND_H

#include "soundsource.h"
#include <opencv2/opencv.hpp>
#include <irrKlang.h>


class Sound
{
public:
    Sound(irrklang::ISound *sound);
    ~Sound();

    float volume() const;
    void setVolume(float volume);
    irrklang::vec3df position() const;
    void setPosition(irrklang::vec3df position);
    bool isLooped() const;
    void setIsLooped(bool looped);
    float minDistance() const;
    void setMinDistance(float min);
    float playbackSpeed() const;
    void setPlaybackSpeed(float speed);
    void stop();
    void drop();

private:
    irrklang::ISound* _sound;

};

#endif // SOUND_H
