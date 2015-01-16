#include "projectbfactory.h"

#include "abstractprojectinfo.h"
#include "abstractprojectwidget.h"

ProjectInfo* ProjectBFactory::createProjectInfo()
{
    return new AbstractProjectInfo("Project B");
}

ProjectWidget* ProjectBFactory::createProjectWidget()
{
   return new AbstractProjectWidget(0, createProjectInfo());
}

ProjectWidget* ProjectBFactory::createProjectWidget(QWidget *parent, ProjectInfo *projectInfo) {
    return new AbstractProjectWidget(parent, projectInfo);
}

