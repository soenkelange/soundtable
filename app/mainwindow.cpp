#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCameraInfo>
#include <QDebug>

Q_DECLARE_METATYPE(QCameraInfo)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openFile()));
    initDevicesMenu();
}

MainWindow::~MainWindow()
{
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

void MainWindow::openCameraDevice(QAction *action) {
    QCameraInfo cameraInfo = qvariant_cast<QCameraInfo>(action->data());
    qDebug() << "MainWindow::openCameraDevice - Device " << cameraInfo.description();
}

void MainWindow::openFile() {
    qDebug() << "MainWindow::openFile";
}


