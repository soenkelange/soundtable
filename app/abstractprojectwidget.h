#ifndef ABSTRACTPROJECTWIDGET_H
#define ABSTRACTPROJECTWIDGET_H

#include "abstractprojectinfo.h"

#include <QWidget>
#include <QLayout>
#include <QLabel>

class AbstractProjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractProjectWidget(QWidget *parent, AbstractProjectInfo *projectInfo);
    virtual ~AbstractProjectWidget();

    AbstractProjectInfo* projectInfo() const;

private:
    AbstractProjectInfo *_projectInfo;
    QLayout *layout;
    QLabel *nameLabel;

};

#endif // ABSTRACTPROJECTWIDGET_H
