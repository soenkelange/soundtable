#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H
#include <irrKlang.h>
#include <QString>
#include <QFileInfo>

using namespace irrklang;

class SoundSource
{
public:
    SoundSource(QString filePath);
    ~SoundSource();

    QString path() const;
    QString name() const;
    int playLength() const;
    void setSoundSource(ISoundSource *soundSource);

private:
    QFileInfo *fileInfo;
    QString _name;
    ISoundSource *_soundSource;
};

#endif // SOUNDSOURCE_H
