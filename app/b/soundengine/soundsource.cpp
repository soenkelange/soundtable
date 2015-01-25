#include "soundsource.h"

SoundSource::SoundSource(irrklang::ISoundSource *source, QString fileName) :
    _soundSource(source)
{
    fileInfo = new QFileInfo(fileName);
    _name = fileInfo->baseName();
}

SoundSource::~SoundSource()
{
    delete fileInfo;
}

QString SoundSource::path() const
{
    return fileInfo->filePath();
}

QString SoundSource::name() const
{
    return _name;
}

int SoundSource::playLength() const
{
    return -1;
}

irrklang::ISoundSource* SoundSource::soundSource() const
{
    return _soundSource;
}
