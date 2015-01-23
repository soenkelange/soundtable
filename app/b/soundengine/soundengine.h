#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include "soundlistener.h"
#include "sound.h"
#include "soundsource.h"
#include <QString>
#include <QStringList>
#include <QSet>

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
    QSet<SoundSource> _soundSources;
    SoundListener _listener;
    float _masterVolume;
};

#endif // SOUNDENGINE_H
