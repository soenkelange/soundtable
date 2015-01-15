#ifndef PROJECTAFACTORY_H
#define PROJECTAFACTORY_H

#include "abstractprojectfactory.h"
#include "projectinfo.h"
#include "projectwidget.h"

class ProjectAFactory : public AbstractProjectFactory
{

public:
    ProjectAFactory() {}
    ~ProjectAFactory() {}
    ProjectInfo* createProjectInfo();
    ProjectWidget* createProjectWidget();

};

#endif // PROJECTAFACTORY_H
