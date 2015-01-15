#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "abstractprojectfactory.h"
#include "projectinfo.h"
#include "projectwidget.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void initDevicesMenu();
    void initProjectsMenu();

    void changeProject(AbstractProjectFactory::PROJECT_FACTORIES newProject);

private slots:
    void openCameraDevice(QAction* action);
    void openFile();
    void openProject(QAction* action);

private:
    Ui::MainWindow *ui;
    AbstractProjectFactory::PROJECT_FACTORIES currentProject;
    ProjectInfo *currentProjectInfo;
    ProjectWidget *currentProjectWidget;
};

#endif // MAINWINDOW_H
