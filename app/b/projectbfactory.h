#ifndef PROJECTBFACTORY_H
#define PROJECTBFACTORY_H

#include "abstractprojectfactory.h"
#include "projectinfo.h"
#include "projectwidget.h"

class ProjectBFactory : public AbstractProjectFactory
{

public:
    ProjectBFactory() {}
    ~ProjectBFactory() {}

    ProjectInfo* createProjectInfo();
    ProjectWidget* createProjectWidget();
    ProjectWidget* createProjectWidget(QWidget *parent, ProjectInfo *projectInfo);

};

#endif // PROJECTBFACTORY_H
