#include "abstractprojectwidget.h"

#include <QHBoxLayout>

AbstractProjectWidget::AbstractProjectWidget(QWidget *parent, ProjectInfo *projectInfo) :
    ProjectWidget(parent)
{
    _projectInfo = projectInfo;

    nameLabel = new QLabel(projectInfo->name());
    nameLabel->setAlignment(Qt::AlignCenter);

    layout = new QVBoxLayout;
    layout->addWidget(nameLabel);
    setLayout(layout);

}

AbstractProjectWidget::~AbstractProjectWidget()
{
    delete nameLabel;
    delete layout;
}

ProjectInfo* AbstractProjectWidget::projectInfo() const
{
    return _projectInfo;
}


