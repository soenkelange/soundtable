#ifndef ABSTRACTPROJECTWIDGET_H
#define ABSTRACTPROJECTWIDGET_H

#include "projectwidget.h"

#include <QLayout>
#include <QLabel>

class AbstractProjectWidget : public ProjectWidget
{
    Q_OBJECT

public:
    explicit AbstractProjectWidget(QWidget *parent = 0, QString projectName = "No project name");
    virtual ~AbstractProjectWidget();

private:
    QLayout *layout;
    QLabel *nameLabel;

};

#endif // ABSTRACTPROJECTWIDGET_H
