#include "abstractprojectinfo.h"

AbstractProjectInfo::AbstractProjectInfo(QString name)
{
    _name = name;
}

QString AbstractProjectInfo::name() const
{
    return _name;
}

