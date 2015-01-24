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
    QSet<SoundSource> _soundSources;
    SoundListener _listener;
    float _masterVolume;

    /*
     * Variablen hier dunter habe ich hinzugefügt.
     * Management für die einzelnen Soundklassen fehlt
     */

    static ISoundEngine* _engine = createIrrKlangDevice();
};

#endif // SOUNDENGINE_H
