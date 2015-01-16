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

    /**
     * Opens the camera which was selected in MainWindow
     *
     * @brief handleOpenCamera
     * @param device to open
     * @return bool true, if the device was opened, or false
     */
    virtual bool handleOpenCamera(int device) = 0;

    /**
     * Opens the file which was selected in MainWindow
     *
     * @brief handleOpenFile
     * @param file
     */
    virtual void handleOpenFile(QString file) = 0;

private:
    AbstractProjectInfo *_projectInfo;
    QLayout *layout;
    QLabel *nameLabel;

};

#endif // ABSTRACTPROJECTWIDGET_H
