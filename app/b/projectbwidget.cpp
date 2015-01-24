#include "projectbwidget.h"
#include "ui_projectbwidget.h"

#include <QDebug>
#include "videoengine.h"
#include <QFile>
#include "soundengine/soundsource.h"

ProjectBWidget::ProjectBWidget(QWidget *parent, AbstractProjectInfo *projectInfo) :
    AbstractProjectWidget(parent, projectInfo),
    ui(new Ui::ProjectBWidget),
    videoPlayer(new VideoPlayer)
{
    ui->setupUi(this);

    setupVideoPlayerConnection();

    // REMOVE - BEGIN
    dirtyHack();
    // REMOVE - END
}

ProjectBWidget::~ProjectBWidget()
{
    delete videoPlayer;
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

void ProjectBWidget::setupVideoPlayerConnection()
{
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
    SoundSource s(filePaht);
    QString name = s.name();
    qDebug() << "Path: " << s.path() << " Name: " << s.name() << " PlayLength: " << s.playLength();
    videoPlayer->setInput(filePaht);
}
