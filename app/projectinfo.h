#ifndef PROJECTINFO
#define PROJECTINFO

#include <QString>

class ProjectInfo
{
public:
    virtual ~ProjectInfo(){}

    virtual QString name() const = 0;
};

#endif // PROJECTINFO

