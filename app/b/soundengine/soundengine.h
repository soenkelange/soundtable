#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H
#include <irrKlang.h>

#include "sound.h"
#include "soundsource.h"
#include <QString>
#include <QStringList>
#include <QSet>
#include <irrKlang.h>
#include "soundlistener.h"

class SoundEngine : public SoundListenerEventListener
{

public:
    SoundEngine();
    ~SoundEngine();

    Sound* play(SoundSource *source, const irrklang::vec3df &postion, bool looped = false);

    SoundSource* load(const QString &fileName);
    QList<SoundSource*> load(const QStringList &fileNames);
    QList<SoundSource*> getSoundSources();

    SoundListener* soundListener();
    void positionChanged();
    void lookDirectionChanged();
    void upVectorChanged();

    float masterVolume() const;
    void setMasterVolume(float volume);
    float defaultMinDistance() const;
    void setDefaultMinDistance(float minDistance);

protected:
    void updateListenerPosition();

private:
    irrklang::ISoundEngine *_engine;
    SoundListener *_listener;
    QList<SoundSource*> _soundSources;
};

#endif // SOUNDENGINE_H
