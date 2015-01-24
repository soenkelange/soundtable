#ifndef PROJECTBFACTORY_H
#define PROJECTBFACTORY_H

#include "abstractprojectfactory.h"
#include "abstractprojectinfo.h"
#include "abstractprojectwidget.h"

class ProjectBFactory : public AbstractProjectFactory
{

public:
    ProjectBFactory() {}
    ~ProjectBFactory() {}

    AbstractProjectInfo* createProjectInfo();
    AbstractProjectWidget* createProjectWidget();
    AbstractProjectWidget* createProjectWidget(QWidget *parent, AbstractProjectInfo *projectInfo);

};

#endif // PROJECTBFACTORY_H
