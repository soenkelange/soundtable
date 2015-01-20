#include "videoplayercontrols.h"
#include "ui_videoplayercontrols.h"

#include <QDebug>

VideoPlayerControls::VideoPlayerControls(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::VideoPlayerControls)
{
    ui->setupUi(this);
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->playButton->setEnabled(true);
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(playClicked()));

    ui->stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->stopButton->setEnabled(false);
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopClicked()));
}

VideoPlayerControls::~VideoPlayerControls()
{
    delete ui;
}

void VideoPlayerControls::setState(VideoPlayer::State state)
{
    qDebug() << "VideoPlayerControls::setState" << state;
    if (state != playerState) {
        switch(state) {
        case VideoPlayer::Stopped:
            ui->stopButton->setEnabled(false);
            ui->playButton->setEnabled(true);
            break;
        case VideoPlayer::Playing:
            ui->stopButton->setEnabled(true);
            ui->playButton->setEnabled(false);
            break;
        }
        playerState = state;
    }
}

void VideoPlayerControls::playClicked()
{
    qDebug() << "VideoPlayerControls::playClicked";
    emit play();
}

void VideoPlayerControls::stopClicked()
{
    qDebug() << "VideoPlayerControls::stopClicked";
    emit stop();
}
