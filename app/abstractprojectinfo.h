#ifndef ABSTRACTPROJECTINFO_H
#define ABSTRACTPROJECTINFO_H

#include <QString>

class AbstractProjectInfo
{

public:
    AbstractProjectInfo(QString name);
    virtual ~AbstractProjectInfo() {}

    QString name() const;

private:
    QString _name;

};

#endif // ABSTRACTPROJECTINFO_H
