#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "abstractprojectfactory.h"
#include "projectinfo.h"
#include "projectwidget.h"

#include <QCameraInfo>
#include <QDebug>

Q_DECLARE_METATYPE(QCameraInfo)
Q_DECLARE_METATYPE(AbstractProjectFactory::PROJECT_FACTORIES)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentProject(AbstractProjectFactory::NO_PROJECT),
    currentProjectWidget(0)
{
    ui->setupUi(this);
    connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openFile()));
    initDevicesMenu();
    initProjectsMenu();
}

MainWindow::~MainWindow()
{
    delete currentProjectInfo;
    delete currentProjectWidget;
    delete ui;
}

void MainWindow::initDevicesMenu() {
    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    QList<QCameraInfo> cameraList = QCameraInfo::availableCameras();
    for(int i = 0; i < cameraList.size(); i++) {
        QCameraInfo cameraInfo = cameraList.at(i);
        QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
        ui->menuOpenDevice->addAction(videoDeviceAction);
    }
    connect(videoDevicesGroup, SIGNAL(triggered(QAction*)), this, SLOT(openCameraDevice(QAction*)));
}

void MainWindow::initProjectsMenu() {
    QActionGroup *projectsGroup = new QActionGroup(this);

    QAction *projectA = new QAction("Projekt A", projectsGroup);
    projectA->setCheckable(true);
    projectA->setData(QVariant::fromValue(AbstractProjectFactory::PROJECT_A));
    ui->menuProjects->addAction(projectA);

    QAction *projectB = new QAction("Projekt B", projectsGroup);
    projectB->setCheckable(true);
    projectB->setData(QVariant::fromValue(AbstractProjectFactory::PROJECT_B));
    ui->menuProjects->addAction(projectB);

    connect(projectsGroup, SIGNAL(triggered(QAction*)), this, SLOT(openProject(QAction*)));
}

void MainWindow::changeProject(AbstractProjectFactory::PROJECT_FACTORIES newProject)
{
    // Nothing will happen, if the same project is already in use
    if(currentProject == newProject) {
        return;
    }

    // Delete old ProjectInfo and ProjectInfo, if there are one
    if (currentProject != AbstractProjectFactory::NO_PROJECT) {
        ui->stackedProjectsWidget->setCurrentIndex(AbstractProjectFactory::NO_PROJECT);
        ui->stackedProjectsWidget->removeWidget(currentProjectWidget);
        delete currentProjectWidget;
        delete currentProjectInfo;
    }

    // Get the factory for the new project
    AbstractProjectFactory *factory = AbstractProjectFactory::createFactory(newProject);
    currentProject = newProject;
    currentProjectInfo = factory->createProjectInfo();
    currentProjectWidget = factory->createProjectWidget();
    ui->stackedProjectsWidget->addWidget(currentProjectWidget);
    ui->stackedProjectsWidget->setCurrentWidget(currentProjectWidget);

    // Deconstruct factory after use
    delete factory;
}

void MainWindow::openCameraDevice(QAction *action) {
    QCameraInfo cameraInfo = qvariant_cast<QCameraInfo>(action->data());
    qDebug() << "MainWindow::openCameraDevice - Device " << cameraInfo.description();
}

void MainWindow::openFile() {
    qDebug() << "MainWindow::openFile";
}

void MainWindow::openProject(QAction *action) {
    AbstractProjectFactory::PROJECT_FACTORIES project =
            qvariant_cast<AbstractProjectFactory::PROJECT_FACTORIES>(action->data());
    changeProject(project);
}


