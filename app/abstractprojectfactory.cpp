#include "abstractprojectfactory.h"

#include "a/projectafactory.h"
#include "b/projectbfactory.h"

AbstractProjectFactory* AbstractProjectFactory::createFactory(PROJECT_FACTORIES factory)
{
    switch(factory) {
        case PROJECT_A:
            return new ProjectAFactory;
        case PROJECT_B:
            return new ProjectBFactory;
        default:
            return 0;
    }
}

