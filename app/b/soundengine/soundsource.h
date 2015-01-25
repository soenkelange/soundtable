#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H

#include <irrKlang.h>
#include <QString>
#include <QFileInfo>

class SoundSource
{
public:
    SoundSource(irrklang::ISoundSource *source, QString filePath);
    ~SoundSource();

    QString path() const;
    QString name() const;
    int playLength() const;

    irrklang::ISoundSource* soundSource() const;

private:
    QFileInfo *fileInfo;
    QString _name;
    irrklang::ISoundSource *_soundSource;
};

#endif // SOUNDSOURCE_H
