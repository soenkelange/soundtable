#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H
#include <irrKlang.h>

#include "sound.h"
#include "soundsource.h"
#include <QString>
#include <QStringList>
#include <QSet>

using namespace irrklang;
class SoundEngine
{
private:
    class SoundListener *_listener;

public:
    SoundEngine();
    ~SoundEngine();

    void play(Sound &sound);
    void load(const QString &fileName);
    void load(const QStringList &fileNames);

    SoundListener* soundListener();

    float masterVolume() const;
    void setMasterVolume(float volume);
    QList<SoundSource>  getSoundSources();

private:
    QList<SoundSource> _soundSources;
    float _masterVolume;
    ISoundEngine* _engine = createIrrKlangDevice();
};

class SoundListener
{
public:
    SoundListener(ISoundEngine* engine);
    ~SoundListener();

    vec3df position() const;
    void setPosition(cv::Point3f position);
    vec3df lookDirection() const;
    void setLookDirection(cv::Point3f direction);
    vec3df upVector() const;
    void setUpVector(cv::Point3f upVector);private:
    vec3df _position = vec3df(0,0,0);
    vec3df _lookDirection = vec3df(0,0,0);
    vec3df _upVector = vec3df(0,0,1);
    ISoundEngine* _engine;
};

#endif // SOUNDENGINE_H
