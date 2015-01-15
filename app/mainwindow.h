#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:
    void openCameraDevice(QAction* action);
    void openFile();
    void openProject(QAction* action);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
