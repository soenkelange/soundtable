#ifndef PROJECTBWIDGET_H
#define PROJECTBWIDGET_H

#include "abstractprojectwidget.h"
#include "abstractprojectinfo.h"
#include "videoengine/videoplayer.h"

namespace Ui {
class ProjectBWidget;
}

class ProjectBWidget : public AbstractProjectWidget
{
    Q_OBJECT

public:
    explicit ProjectBWidget(QWidget *parent = 0, AbstractProjectInfo *projectInfo = 0);
    ~ProjectBWidget();

    void setupVideoPlayerConnection();

    bool handleOpenCamera(int device);
    void handleOpenFile(QString filePath);

private:
    Ui::ProjectBWidget *ui;
    VideoPlayer *videoPlayer;
};

#endif // PROJECTBWIDGET_H
