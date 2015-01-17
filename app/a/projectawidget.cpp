#include "projectawidget.h"
#include "ui_projectawidget.h"

ProjectAWidget::ProjectAWidget(QWidget *parent, AbstractProjectInfo *projectInfo) :
    AbstractProjectWidget(parent, projectInfo),
    ui(new Ui::ProjectAWidget)
{
    ui->setupUi(this);
}

ProjectAWidget::~ProjectAWidget()
{
    delete ui;
}
