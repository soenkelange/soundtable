#include "videooutputtabwidget.h"
#include "ui_videooutputtabwidget.h"

VideoOutputTabWidget::VideoOutputTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::VideoOutputTabWidget)
{
    ui->setupUi(this);
}

VideoOutputTabWidget::~VideoOutputTabWidget()
{
    delete ui;
}
