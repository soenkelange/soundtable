#include "soundengine.h"


SoundEngine::SoundEngine()
{

}

SoundEngine::~SoundEngine()
{

}

void SoundEngine::play(const Sound &sound)
{
    ISound* _sound = _engine->play3D(sound.getSoundSource().path(),sound.position(), sound.isLooped(), false, true);
    sound.setSound(_sound);

}

void SoundEngine::load(const QString &fileName)
{


}

void SoundEngine::load(const QStringList &fileNames)
{
    for(int i = 0; i <= fileNames.size(); i++) {
        load(fileNames.at(i));
    }
}

SoundListener SoundEngine::soundListener() const
{
    return _listener;
}

float SoundEngine::masterVolume() const
{
    return _masterVolume;
}

void SoundEngine::setMasterVolume(float volume)
{
    _masterVolume = volume;
    engine->setSoundVolume(_masterVolume);
}
