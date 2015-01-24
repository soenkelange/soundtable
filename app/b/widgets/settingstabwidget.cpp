#include "settingstabwidget.h"
#include "ui_settingstabwidget.h"

SettingsTabWidget::SettingsTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::SettingsTabWidget)
{
    ui->setupUi(this);
}

SettingsTabWidget::~SettingsTabWidget()
{
    delete ui;
}
