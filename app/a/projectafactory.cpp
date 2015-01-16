#include "projectafactory.h"

#include "abstractprojectinfo.h"
#include "abstractprojectwidget.h"

AbstractProjectInfo* ProjectAFactory::createProjectInfo()
{
    return new AbstractProjectInfo("Project A");
}

AbstractProjectWidget* ProjectAFactory::createProjectWidget()
{
   return new AbstractProjectWidget(0, createProjectInfo());
}

AbstractProjectWidget* ProjectAFactory::createProjectWidget(QWidget *parent, AbstractProjectInfo *projectInfo) {
    return new AbstractProjectWidget(parent, projectInfo);
}

