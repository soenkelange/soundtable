#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H

#include <QString>
#include <QFileInfo>

class SoundSource
{
public:
    SoundSource(QString filePath);
    ~SoundSource();

    QString path() const;
    QString name() const;
    int playLength() const;

private:
    QFileInfo *fileInfo;
    QString _name;
};

#endif // SOUNDSOURCE_H
