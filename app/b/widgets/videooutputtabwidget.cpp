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

VideoWidget* VideoOutputTabWidget::getInputWidget()
{
    return ui->inputVideoWidget;
}

VideoWidget* VideoOutputTabWidget::getOutputWidget()
{
    return ui->outputVideoWidget;
}
