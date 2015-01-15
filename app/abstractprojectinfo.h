#ifndef ABSTRACTPROJECTINFO_H
#define ABSTRACTPROJECTINFO_H

#include "projectinfo.h"

class AbstractProjectInfo : public ProjectInfo
{

public:
    AbstractProjectInfo(QString name);
    virtual ~AbstractProjectInfo() {}

    QString name() const;

private:
    QString _name;

};

#endif // ABSTRACTPROJECTINFO_H
