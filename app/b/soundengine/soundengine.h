#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H
#include <irrKlang.h>
#include "soundlistener.h"
#include "sound.h"
#include "soundsource.h"
#include <QString>
#include <QStringList>
#include <QSet>

using namespace irrklang;
class SoundEngine
{
public:
    SoundEngine();
    ~SoundEngine();

    void play(const Sound &sound);
    void load(const QString &fileName);
    void load(const QStringList &fileNames);

    SoundListener soundListener() const;

    float masterVolume() const;
    void setMasterVolume(float volume);

private:
    ISoundEngine* _engine = createIrrKlangDevice();
    QSet<SoundSource> _soundSources;
    SoundListener _listener;
    float _masterVolume;
    ISound* _sound;
};

#endif // SOUNDENGINE_H
