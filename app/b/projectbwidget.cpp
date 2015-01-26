#include "projectbwidget.h"
#include "ui_projectbwidget.h"

#include <QDebug>
#include <QFile>

ProjectBWidget::ProjectBWidget(QWidget *parent, AbstractProjectInfo *projectInfo) :
    AbstractProjectWidget(parent, projectInfo),
    ui(new Ui::ProjectBWidget),
    soundTable(new SoundTable),
    videoPlayer(new VideoPlayer),
    processorSettings(new CardsProcessorSettings),
    soundEngineSettings(new SoundEngineSettings)
{
    ui->setupUi(this);

    initVideoPlayer();
    initSettingTabs();

    // REMOVE - BEGIN
    dirtyHack();
    // REMOVE - END
}

ProjectBWidget::~ProjectBWidget()
{
    delete processorSettings;
    delete soundEngineSettings;
    delete videoPlayer;
    delete soundTable;
    delete ui;
}

// REMOVE - BEGIN
void ProjectBWidget::dirtyHack()
{
    QString testFile = "/Users/soenkelange/ownCloud/AVPRG/Testvideos/out.mpeg";
    handleOpenFile(testFile);
    videoPlayer->play();
}
// REMOVE - END

void ProjectBWidget::initSettingTabs()
{
    ui->settingsWidget->addTab(processorSettings, "Prozessor");
    processorSettings->setCardsProcessor(soundTable->cardProcessor());
    ui->settingsWidget->addTab(soundEngineSettings, "Audio");
    soundEngineSettings->setSoundEngine(soundTable->soundEngine());
}

void ProjectBWidget::initVideoPlayer()
{
    // Connect with processor
    videoPlayer->setVideoProcessor(soundTable->cardProcessor());

    // Connect with controls
    connect(ui->videoPlayerControls, SIGNAL(play()), videoPlayer, SLOT(play()));
    connect(ui->videoPlayerControls, SIGNAL(stop()), videoPlayer, SLOT(stop()));

    connect(videoPlayer, SIGNAL(stateChanged(VideoPlayer::State)),
                ui->videoPlayerControls,
                SLOT(setState(VideoPlayer::State)));
    ui->videoPlayerControls->setState(videoPlayer->state());

    //Connect with video output
    videoPlayer->setInputVideoWidget(ui->videoOutputWidget->getInputWidget());
    videoPlayer->setOutputVideoWidget(ui->videoOutputWidget->getOutputWidget());
}

bool ProjectBWidget::handleOpenCamera(int device)
{
    return videoPlayer->setInput(device);
}

void ProjectBWidget::handleOpenFile(QString filePaht) {
    videoPlayer->setInput(filePaht);
}
