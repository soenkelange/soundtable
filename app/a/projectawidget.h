#ifndef PROJECTAWIDGET_H
#define PROJECTAWIDGET_H

#include "abstractprojectwidget.h"
#include "abstractprojectinfo.h"

namespace Ui {
class ProjectAWidget;
}

class ProjectAWidget : public AbstractProjectWidget
{
    Q_OBJECT

public:
    explicit ProjectAWidget(QWidget *parent = 0, AbstractProjectInfo *projectInfo = 0);
    ~ProjectAWidget();

    // TODO: Implement this functions
    bool handleOpenCamera(int device) {
        return false;
    }
    void handleOpenFile(QString file) {
        return;
    }
    // END TODO

private:
    Ui::ProjectAWidget *ui;
};

#endif // PROJECTAWIDGET_H
