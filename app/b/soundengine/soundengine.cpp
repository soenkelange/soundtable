#include "soundengine.h"

#include <QDebug>
#include <irrKlang.h>

SoundEngine::SoundEngine() :
    _engine(irrklang::createIrrKlangDevice()),
    _soundSources(),
    _listener(0)
{
    _listener = new SoundListener(this);
    qDebug() << _engine->isMultiThreaded();
}

SoundEngine::~SoundEngine()
{
    _engine->drop();
    delete _listener;
}

Sound* SoundEngine::play(SoundSource *source, const irrklang::vec3df &postion, bool looped)
{
    irrklang::ISound *iSound = _engine->play3D(source->soundSource(), postion, looped, false, true);
    Sound *sound = new Sound(iSound);
    qDebug() << "Play " << source->name();
    return sound;
}

SoundSource* SoundEngine::load(const QString &fileName)
{
    irrklang::ISoundSource *source =_engine->addSoundSourceFromFile(
                fileName.toLocal8Bit().constData(), irrklang::ESM_AUTO_DETECT);
    SoundSource *soundSource = new SoundSource(source, fileName);
    _soundSources.append(soundSource);
    qDebug() << "Loaded " << soundSource->name();
    return soundSource;
}

QList<SoundSource*> SoundEngine::load(const QStringList &fileNames)
{
    QList<SoundSource*> loadedSources;
    for(int i = 0; i <= fileNames.size(); i++) {
        SoundSource *source = load(fileNames.at(i));
        loadedSources.append(source);
    }
    return loadedSources;
}

QList<SoundSource *> SoundEngine::getSoundSources()
{
    return _soundSources;
}

SoundListener* SoundEngine::soundListener()
{
    return _listener;
}

void SoundEngine::positionChanged()
{
    updateListenerPosition();
}

void SoundEngine::lookDirectionChanged()
{
    updateListenerPosition();
}

void SoundEngine::upVectorChanged()
{
    updateListenerPosition();
}

void SoundEngine::updateListenerPosition()
{
    _engine->setListenerPosition(_listener->position(), _listener->lookDirection(),
                                 irrklang::vec3df(0,0,0), _listener->upVector());
}

float SoundEngine::masterVolume() const
{
    return _engine->getSoundVolume();
}

void SoundEngine::setMasterVolume(float volume)
{
    qDebug() << "setmastervolume" << QString::number(volume);
    _engine->setSoundVolume(volume);
}

float SoundEngine::defaultMinDistance() const
{
    return _engine->getDefault3DSoundMinDistance();
}

void SoundEngine::setDefaultMinDistance(float minDistance) {
    qDebug() << "Set defaultMinDistance: " << QString::number(minDistance);
    _engine->setDefault3DSoundMinDistance(minDistance);
}
