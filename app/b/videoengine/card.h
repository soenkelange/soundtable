#ifndef CARD_H
#define CARD_H

#include <vector>
#include <opencv2/opencv.hpp>
#include <QDebug>

class Card
{

private:
    class CardEventListener *_listener;

public:
    enum Color {
        Yellow,
        Red,
        Blue
    };

    enum Shape {
        Triangle,
        Square,
        Hexagon,
        Circle,
        Star
    };

    Card(Card::Color color, Card::Shape shape);
    ~Card();

    Card::Color color() const;
    cv::Scalar colorAsScalar() const;
    QString colorName() const;
    Card::Shape shape() const;
    QString shapeName() const;
    cv::Point2f position() const;
    void setPosition(cv::Point2f position);
    float rotation() const;
    void setRotation(float rotation);
    bool isVisible() const;
    void setVisibility(bool visible);
    bool isDetected() const;
    void setDetected(bool detected);

    void setListener(CardEventListener *listener);
    void removeListener();

private:
    Card::Color _color;
    Card::Shape _shape;
    cv::Point2f _position;
    float _rotation;
    bool _visible;
    bool _detected;

};
QDebug operator<< ( QDebug debug, const Card &card);

class CardEventListener
{

public:
    virtual ~CardEventListener();

    virtual void positionChanged(const Card &card, cv::Point2f oldPosition) = 0;
    virtual void rotationChanged(const Card &card, int oldRotation) = 0;
    virtual void visibilityChanged(const Card &card);
};

#endif // CARD_H
