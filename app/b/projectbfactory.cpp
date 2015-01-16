#include "projectbfactory.h"

#include "abstractprojectinfo.h"
#include "projectbwidget.h"

AbstractProjectInfo* ProjectBFactory::createProjectInfo()
{
    return new AbstractProjectInfo("Project B");
}

AbstractProjectWidget* ProjectBFactory::createProjectWidget()
{
   return createProjectWidget(0, createProjectInfo());
}

AbstractProjectWidget* ProjectBFactory::createProjectWidget(QWidget *parent, AbstractProjectInfo *projectInfo) {
    return new ProjectBWidget(parent, projectInfo);
}

