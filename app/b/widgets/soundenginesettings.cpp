#include "soundenginesettings.h"
#include "ui_soundenginesettings.h"

SoundEngineSettings::SoundEngineSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundEngineSettings)
{
    ui->setupUi(this);
}

SoundEngineSettings::~SoundEngineSettings()
{
    delete ui;
}

void SoundEngineSettings::setSoundEngine(SoundEngine *soundEngine)
{
    _soundEngine = soundEngine;

    // master volume
    ui->masterVolumeSlider->setValue(_soundEngine->masterVolume()*100);
    connect(ui->masterVolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(setMasterVolume(int)));
    // min distance
    ui->minDistanceSlider->setValue(_soundEngine->defaultMinDistance());
    connect(ui->minDistanceSlider, SIGNAL(valueChanged(int)), this, SLOT(setDefaultMinDistance(int)));
}

void SoundEngineSettings::setMasterVolume(int volume)
{
    float _volume = ((float) volume)*0.01;
    _soundEngine->setMasterVolume(_volume);
}

void SoundEngineSettings::setDefaultMinDistance(int minDistance)
{
    _soundEngine->setDefaultMinDistance(minDistance);
}


