#include "soundsource.h"

SoundSource::SoundSource(QString fileName)
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

