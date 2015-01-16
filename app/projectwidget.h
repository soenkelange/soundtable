#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QWidget>

class ProjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectWidget(QWidget *parent = 0) : QWidget(parent) {}
    virtual ~ProjectWidget() {}

};

#endif // PROJECTWIDGET_H
