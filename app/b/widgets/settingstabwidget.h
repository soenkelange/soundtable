#ifndef SETTINGSTABWIDGET_H
#define SETTINGSTABWIDGET_H

#include <QTabWidget>

namespace Ui {
class SettingsTabWidget;
}

class SettingsTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit SettingsTabWidget(QWidget *parent = 0);
    ~SettingsTabWidget();

private:
    Ui::SettingsTabWidget *ui;
};

#endif // SETTINGSTABWIDGET_H
