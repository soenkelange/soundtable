#ifndef VIDEOOUTPUTTABWIDGET_H
#define VIDEOOUTPUTTABWIDGET_H

#include <QTabWidget>

namespace Ui {
class VideoOutputTabWidget;
}

class VideoOutputTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit VideoOutputTabWidget(QWidget *parent = 0);
    ~VideoOutputTabWidget();

private:
    Ui::VideoOutputTabWidget *ui;
};

#endif // VIDEOOUTPUTTABWIDGET_H
