#ifndef ABSTRACTPROJECTWIDGET_H
#define ABSTRACTPROJECTWIDGET_H

#include "projectwidget.h"
#include "projectinfo.h"

#include <QLayout>
#include <QLabel>

class AbstractProjectWidget : public ProjectWidget
{
    Q_OBJECT

public:
    explicit AbstractProjectWidget(QWidget *parent, ProjectInfo *projectInfo);
    virtual ~AbstractProjectWidget();

    ProjectInfo* projectInfo() const;

private:
    ProjectInfo *_projectInfo;
    QLayout *layout;
    QLabel *nameLabel;

};

#endif // ABSTRACTPROJECTWIDGET_H
