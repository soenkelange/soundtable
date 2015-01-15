#include "projectafactory.h"

#include "abstractprojectinfo.h"
#include "abstractprojectwidget.h"

ProjectInfo* ProjectAFactory::createProjectInfo()
{
    return new AbstractProjectInfo("Project A");
}

ProjectWidget* ProjectAFactory::createProjectWidget()
{
   return new AbstractProjectWidget(0, "Project A");
}

