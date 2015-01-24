#ifndef VIDEOPLAYERCONTROLS_H
#define VIDEOPLAYERCONTROLS_H

#include "../videoengine/videoplayer.h"
#include <QGroupBox>

namespace Ui {
class VideoPlayerControls;
}

class VideoPlayerControls : public QGroupBox
{
    Q_OBJECT

public:
    explicit VideoPlayerControls(QWidget *parent = 0);
    ~VideoPlayerControls();

public slots:
    void setState(VideoPlayer::State state);

signals:
    void play();
    void stop();

private slots:
    void playClicked();
    void stopClicked();

private:
    Ui::VideoPlayerControls *ui;
    VideoPlayer::State playerState;
};

#endif // VIDEOPLAYERCONTROLS_H
