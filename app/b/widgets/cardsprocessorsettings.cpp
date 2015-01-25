#include "cardsprocessorsettings.h"
#include "ui_cardsprocessorsettings.h"

#include <QSlider>
#include <QLineEdit>

CardsProcessorSettings::CardsProcessorSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardsProcessorSettings),
    _processor(0),
    _currentCKColor(CardsProcessor::Yellow)
{
    ui->setupUi(this);
    initColorKeyingSlider();
}

CardsProcessorSettings::~CardsProcessorSettings()
{
    delete ui;
}

void CardsProcessorSettings::initColorKeyingSlider()
{
    connect(ui->lowerHueSlider, SIGNAL(valueChanged(int)), this, SLOT(updateLowerHueLineEdit(int)));
    connect(ui->upperHueSlider, SIGNAL(valueChanged(int)), this, SLOT(updateUpperHueLineEdit(int)));
    connect(ui->lowerSatSlider, SIGNAL(valueChanged(int)), this, SLOT(updateLowerSatLineEdit(int)));
    connect(ui->upperSatSlider, SIGNAL(valueChanged(int)), this, SLOT(updateUpperSatLineEdit(int)));
    connect(ui->lowerValueSlider, SIGNAL(valueChanged(int)), this, SLOT(updateLowerValueLineEdit(int)));
    connect(ui->upperValueSlider, SIGNAL(valueChanged(int)), this, SLOT(updateUpperValueLineEdit(int)));

    ui->colorSelector->addItem("Gelb", QVariant(CardsProcessor::Yellow));
    ui->colorSelector->addItem("Rot", QVariant(CardsProcessor::Red));
    ui->colorSelector->addItem("Blau", QVariant(CardsProcessor::Blue));
    connect(ui->colorSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedColorChanged(int)));
    selectedColorChanged(ui->colorSelector->currentIndex());
}

void CardsProcessorSettings::setCardsProcessor(CardsProcessor *processor)
{
    _processor = processor;

    // Threshold
    ui->thresholdSlider->setValue(_processor->threshold());
    connect(ui->thresholdSlider, SIGNAL(valueChanged(int)), _processor, SLOT(setThreshold(int)));

    // Canny
    ui->cLowerThresholdSlider->setValue(_processor->cannyLowerThreshold());
    connect(ui->cLowerThresholdSlider, SIGNAL(valueChanged(int)), _processor, SLOT(setCannyLowerThreshold(int)));
    ui->cUpperThresholdSlider->setValue(_processor->cannyUpperThreshold());
    connect(ui->cUpperThresholdSlider, SIGNAL(valueChanged(int)), _processor, SLOT(setCannyUpperThreshold(int)));
    ui->cGradientCheckBox->setChecked(_processor->cannyGradient());
    connect(ui->cGradientCheckBox, SIGNAL(toggled(bool)), _processor, SLOT(setCannyGradient(bool)));

    // Color Keying
    updateColorKeyingComponents();
}

void CardsProcessorSettings::updateLowerHueLineEdit(int value) {
    ui->lowerHueLineEdit->setText(QString::number(value));
    CardsProcessor::CK_Range range = CardsProcessor::Lower;
    CardsProcessor::CK_HSV hsv = CardsProcessor::Hue;
    setColorKeyingValue(range, hsv, value);
}

void CardsProcessorSettings::updateUpperHueLineEdit(int value) {
    ui->upperHueLineEdit->setText(QString::number(value));
    CardsProcessor::CK_Range range = CardsProcessor::Upper;
    CardsProcessor::CK_HSV hsv = CardsProcessor::Hue;
    setColorKeyingValue(range, hsv, value);
}

void CardsProcessorSettings::updateLowerSatLineEdit(int value) {
    ui->lowerSatLineEdit->setText(QString::number(value));
    CardsProcessor::CK_Range range = CardsProcessor::Lower;
    CardsProcessor::CK_HSV hsv = CardsProcessor::Saturation;
    setColorKeyingValue(range, hsv, value);
}

void CardsProcessorSettings::updateUpperSatLineEdit(int value) {
    ui->upperSatLineEdit->setText(QString::number(value));
    CardsProcessor::CK_Range range = CardsProcessor::Upper;
    CardsProcessor::CK_HSV hsv = CardsProcessor::Saturation;
    setColorKeyingValue(range, hsv, value);
}

void CardsProcessorSettings::updateLowerValueLineEdit(int value) {
    ui->lowerValueLineEdit->setText(QString::number(value));
    CardsProcessor::CK_Range range = CardsProcessor::Lower;
    CardsProcessor::CK_HSV hsv = CardsProcessor::Value;
    setColorKeyingValue(range, hsv, value);
}

void CardsProcessorSettings::updateUpperValueLineEdit(int value) {
    ui->upperValueLineEdit->setText(QString::number(value));
    CardsProcessor::CK_Range range = CardsProcessor::Upper;
    CardsProcessor::CK_HSV hsv = CardsProcessor::Value;
    setColorKeyingValue(range, hsv, value);
}

void CardsProcessorSettings::setColorKeyingValue(CardsProcessor::CK_Range range,
                                                 CardsProcessor::CK_HSV hsv,
                                                 int value)
{
    if (_processor == 0) {
        qDebug() << "No processor.";
        return;
    }
    /* DEBUG BEGIN
    QString rangeName;
    switch(range) {
    case CardsProcessor::Lower:
        rangeName = "Lower";
        break;
    case CardsProcessor::Upper:
        rangeName = "Upper";
        break;
    default:
        rangeName = "Invalid range";
    }

    QString hsvName;
    switch(hsv) {
    case CardsProcessor::Hue:
        hsvName = "Hue";
        break;
    case CardsProcessor::Saturation:
        hsvName = "Saturation";
        break;
    case CardsProcessor::Value:
        hsvName = "Value";
        break;
    default:
        hsvName = "Invalid hsv value";
    }

    QString colorName;
    switch(_currentCKColor) {
    case CardsProcessor::Yellow:
        colorName = "Yellow";
        break;
    case CardsProcessor::Red:
        colorName = "Red";
        break;
    case CardsProcessor::Blue:
        colorName = "Blue";
        break;
    default:
        colorName = "Invalid color";
    }
    qDebug() << "Set " << rangeName << " " << hsvName << " of color " << colorName << " to " << value;
    DEBUG END */

    _processor->setColorKeyingOption(_currentCKColor, range, hsv, value);
}

void CardsProcessorSettings::selectedColorChanged(int index)
{
    int data = ui->colorSelector->itemData(index).toInt();
    switch(data) {
    case CardsProcessor::Yellow:
        qDebug() << "Yellow selected";
        _currentCKColor = CardsProcessor::Yellow;
        break;
    case CardsProcessor::Red:
        qDebug() << "Red selected";
        _currentCKColor = CardsProcessor::Red;
        break;
    case CardsProcessor::Blue:
        qDebug() << "Blue selected";
        _currentCKColor = CardsProcessor::Blue;
        break;
    default:
        _currentCKColor = CardsProcessor::Yellow;
    }
    if (_processor != 0) {
        updateColorKeyingComponents();
    }
}

void CardsProcessorSettings::updateColorKeyingComponents()
{
    ui->lowerHueSlider->setValue(_processor->getColorKeyingOption(_currentCKColor,
                                                                  CardsProcessor::Lower,
                                                                  CardsProcessor::Hue));
    ui->upperHueSlider->setValue(_processor->getColorKeyingOption(_currentCKColor,
                                                                  CardsProcessor::Upper,
                                                                  CardsProcessor::Hue));
    ui->lowerSatSlider->setValue(_processor->getColorKeyingOption(_currentCKColor,
                                                                  CardsProcessor::Lower,
                                                                  CardsProcessor::Saturation));
    ui->upperSatSlider->setValue(_processor->getColorKeyingOption(_currentCKColor,
                                                                  CardsProcessor::Upper,
                                                                  CardsProcessor::Saturation));
    ui->lowerValueSlider->setValue(_processor->getColorKeyingOption(_currentCKColor,
                                                                  CardsProcessor::Lower,
                                                                  CardsProcessor::Value));
    ui->upperValueSlider->setValue(_processor->getColorKeyingOption(_currentCKColor,
                                                                  CardsProcessor::Upper,
                                                                  CardsProcessor::Value));
}
