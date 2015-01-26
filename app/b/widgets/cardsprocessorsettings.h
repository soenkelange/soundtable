#ifndef CARDSPROCESSORSETTINGS_H
#define CARDSPROCESSORSETTINGS_H

#include <QWidget>
#include "../videoengine/cardsprocessor.h"

namespace Ui {
class CardsProcessorSettings;
}

class CardsProcessorSettings : public QWidget
{
    Q_OBJECT

public:
    explicit CardsProcessorSettings(QWidget *parent = 0);
    ~CardsProcessorSettings();

    void setCardsProcessor(CardsProcessor *processor);

protected slots:
    void updateLowerHueLineEdit(int value);
    void updateUpperHueLineEdit(int value);
    void updateLowerSatLineEdit(int value);
    void updateUpperSatLineEdit(int value);
    void updateLowerValueLineEdit(int value);
    void updateUpperValueLineEdit(int value);
    void selectedColorChanged(int index);
    void selectedOutputChanged(int index);
    void updateColorKeyingComponents();

protected:
    void initColorKeyingSlider();
    void setColorKeyingValue(CardsProcessor::CK_Range range, CardsProcessor::CK_HSV hsv, int value);

private:
    Ui::CardsProcessorSettings *ui;
    CardsProcessor *_processor;
    CardsProcessor::CK_Color _currentCKColor;
};

#endif // CARDSPROCESSORSETTINGS_H
