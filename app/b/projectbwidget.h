#ifndef PROJECTBWIDGET_H
#define PROJECTBWIDGET_H

#include "abstractprojectwidget.h"
#include "abstractprojectinfo.h"
#include "soundtable.h"
#include "videoengine/videoplayer.h"
#include "videoengine/cardsprocessor.h"
#include "widgets/cardsprocessorsettings.h"
#include "widgets/soundenginesettings.h"

namespace Ui {
class ProjectBWidget;
}

class ProjectBWidget : public AbstractProjectWidget
{
    Q_OBJECT

public:
    explicit ProjectBWidget(QWidget *parent = 0, AbstractProjectInfo *projectInfo = 0);
    ~ProjectBWidget();

    void initSettingTabs();
    void initVideoPlayer();

    bool handleOpenCamera(int device);
    void handleOpenFile(QString filePath);

private:
    Ui::ProjectBWidget *ui;
    SoundTable *soundTable;
    VideoPlayer *videoPlayer;
    CardsProcessorSettings *processorSettings;
    SoundEngineSettings *soundEngineSettings;
};

#endif // PROJECTBWIDGET_H
