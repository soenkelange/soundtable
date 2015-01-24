#ifndef PROJECTFACTORY_H
#define PROJECTFACTORY_H

#include "abstractprojectinfo.h"
#include "abstractprojectwidget.h"

class AbstractProjectFactory
{
public:
    enum PROJECT_FACTORIES {
        NO_PROJECT = 0,
        PROJECT_A = 1,
        PROJECT_B = 2,
    };

    virtual ~AbstractProjectFactory(){}

    virtual AbstractProjectInfo* createProjectInfo() = 0;
    Q_DECL_DEPRECATED virtual AbstractProjectWidget* createProjectWidget() = 0;
    virtual AbstractProjectWidget* createProjectWidget(QWidget *parent, AbstractProjectInfo *projectInfo) = 0;

    static AbstractProjectFactory* createFactory(PROJECT_FACTORIES factory);
};

#endif // PROJECTFACTORY_H
