#include "projectbwidget.h"
#include "ui_projectbwidget.h"

ProjectBWidget::ProjectBWidget(QWidget *parent, AbstractProjectInfo *projectInfo) :
    AbstractProjectWidget(parent, projectInfo),
    ui(new Ui::ProjectBWidget)
{
    ui->setupUi(this);
    //ui->projectName->setText(projectInfo->name());
}

ProjectBWidget::~ProjectBWidget()
{
    delete ui;
}

bool ProjectBWidget::handleOpenCamera(int device)
{
    //ui->selectedVideoInput->setText("Open device");
    return true;
}

void ProjectBWidget::handleOpenFile(QString filePaht) {
    //ui->selectedVideoInput->setText("Open file");
}
