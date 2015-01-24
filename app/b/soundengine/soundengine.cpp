#include "soundengine.h"


SoundEngine::SoundEngine()
{

}

SoundEngine::~SoundEngine()
{

}

void SoundEngine::play(Sound &sound )
{
    ISound* _sound = _engine->play3D("sound.getSoundSource().path()", sound.position(), sound.isLooped(), false, true);
    sound.setSound(_sound);

}


void SoundEngine::load(const QString &fileName)
{
    SoundSource soundSource(fileName);

    ISoundSource *iSoundSource =_engine->addSoundSourceFromFile(fileName.toLocal8Bit().constData(),ESM_AUTO_DETECT);
    soundSource.setSoundSource(iSoundSource);
    _soundSources.append(soundSource);

}

QList<SoundSource> SoundEngine::getSoundSources()
{
    return _soundSources;
}

void SoundEngine::load(const QStringList &fileNames)
{
    for(int i = 0; i <= fileNames.size(); i++) {
        load(fileNames.at(i));
    }
}

SoundListener* SoundEngine::soundListener()
{
    return _listener;
}

float SoundEngine::masterVolume() const
{
    return _masterVolume;
}

void SoundEngine::setMasterVolume(float volume)
{
    if(volume >1)
    {
        volume = 1;
    }else if(volume <0)
    {
        voulume = 0;
    }
    _masterVolume = volume;
    _engine->setSoundVolume(_masterVolume);
}
