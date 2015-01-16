#include "abstractprojectwidget.h"

#include <QHBoxLayout>

AbstractProjectWidget::AbstractProjectWidget(QWidget *parent, QString projectName) :
    ProjectWidget(parent)
{
    nameLabel = new QLabel(projectName);
    nameLabel->setAlignment(Qt::AlignCenter);

    layout = new QVBoxLayout;
    layout->addWidget(nameLabel);
    setLayout(layout);

}

AbstractProjectWidget::~AbstractProjectWidget()
{
    delete nameLabel;
    delete layout;
}
