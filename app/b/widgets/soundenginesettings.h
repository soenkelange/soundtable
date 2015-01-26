#ifndef SOUNDENGINESETTINGS_H
#define SOUNDENGINESETTINGS_H

#include <QWidget>
#include "../soundengine/soundengine.h"

namespace Ui {
class SoundEngineSettings;
}

class SoundEngineSettings : public QWidget
{
    Q_OBJECT

public:
    explicit SoundEngineSettings(QWidget *parent = 0);
    ~SoundEngineSettings();

    void setSoundEngine(SoundEngine *soundEngine);
public slots:
    void setMasterVolume(int volume);
    void setDefaultMinDistance(int minDistance);

private:
    Ui::SoundEngineSettings *ui;
    SoundEngine *_soundEngine;
};

#endif // SOUNDENGINESETTINGS_H
