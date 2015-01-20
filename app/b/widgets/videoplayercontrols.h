#ifndef VIDEOPLAYERCONTROLS_H
#define VIDEOPLAYERCONTROLS_H

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

private:
    Ui::VideoPlayerControls *ui;
};

#endif // VIDEOPLAYERCONTROLS_H
