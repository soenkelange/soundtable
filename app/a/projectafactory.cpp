#include "projectafactory.h"

#include "abstractprojectinfo.h"
#include "abstractprojectwidget.h"

ProjectInfo* ProjectAFactory::createProjectInfo()
{
    return new AbstractProjectInfo("Project A");
}

ProjectWidget* ProjectAFactory::createProjectWidget()
{
   return new AbstractProjectWidget(0, createProjectInfo());
}

ProjectWidget* ProjectAFactory::createProjectWidget(QWidget *parent, ProjectInfo *projectInfo) {
    return new AbstractProjectWidget(parent, projectInfo);
}

