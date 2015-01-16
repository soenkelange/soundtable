#include "projectbfactory.h"

#include "abstractprojectinfo.h"
#include "abstractprojectwidget.h"

AbstractProjectInfo* ProjectBFactory::createProjectInfo()
{
    return new AbstractProjectInfo("Project B");
}

AbstractProjectWidget* ProjectBFactory::createProjectWidget()
{
   return new AbstractProjectWidget(0, createProjectInfo());
}

AbstractProjectWidget* ProjectBFactory::createProjectWidget(QWidget *parent, AbstractProjectInfo *projectInfo) {
    return new AbstractProjectWidget(parent, projectInfo);
}

