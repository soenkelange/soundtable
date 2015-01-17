#ifndef PROJECTBWIDGET_H
#define PROJECTBWIDGET_H

#include "abstractprojectwidget.h"
#include "abstractprojectinfo.h"

namespace Ui {
class ProjectBWidget;
}

class ProjectBWidget : public AbstractProjectWidget
{
    Q_OBJECT

public:
    explicit ProjectBWidget(QWidget *parent = 0, AbstractProjectInfo *projectInfo = 0);
    ~ProjectBWidget();

    bool handleOpenCamera(int device);
    void handleOpenFile(QString filePath);

private:
    Ui::ProjectBWidget *ui;
};

#endif // PROJECTBWIDGET_H
