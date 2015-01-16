#ifndef PROJECTFACTORY_H
#define PROJECTFACTORY_H

#include "projectinfo.h"
#include "projectwidget.h"

class AbstractProjectFactory
{
public:
    enum PROJECT_FACTORIES {
        NO_PROJECT = 0,
        PROJECT_A = 1,
        PROJECT_B = 2,
    };

    virtual ~AbstractProjectFactory(){}

    virtual ProjectInfo* createProjectInfo() = 0;
    virtual ProjectWidget* createProjectWidget() = 0;
    virtual ProjectWidget* createProjectWidget(QWidget *parent, ProjectInfo *projectInfo) = 0;

    static AbstractProjectFactory* createFactory(PROJECT_FACTORIES factory);
};

#endif // PROJECTFACTORY_H
