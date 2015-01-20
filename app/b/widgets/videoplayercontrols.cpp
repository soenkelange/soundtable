#include "videoplayercontrols.h"
#include "ui_videoplayercontrols.h"

VideoPlayerControls::VideoPlayerControls(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::VideoPlayerControls)
{
    ui->setupUi(this);
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
}

VideoPlayerControls::~VideoPlayerControls()
{
    delete ui;
}
