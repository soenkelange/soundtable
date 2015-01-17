#include "abstractprojectwidget.h"

#include <QHBoxLayout>

AbstractProjectWidget::AbstractProjectWidget(QWidget *parent, AbstractProjectInfo *projectInfo) :
    QWidget(parent)
{
    _projectInfo = projectInfo;
}

AbstractProjectWidget::~AbstractProjectWidget()
{
}

AbstractProjectInfo* AbstractProjectWidget::projectInfo() const
{
    return _projectInfo;
}


