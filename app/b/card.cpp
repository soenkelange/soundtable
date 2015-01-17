#include "card.h"

#include <opencv2/opencv.hpp>
#include <QDebug>

Card::Card(Color color, Shape shape) :
    _position(0,0)
{
    _color = color;
    _shape = shape;
    _rotation = 0;
}

Card::~Card()
{

}

Card::Color Card::color() const
{
    return _color;
}

Card::Shape Card::shape() const
{
    return _shape;
}

cv::Point2f Card::position() const
{
    return _position;
}

void Card::setPosition(cv::Point2f newPosition)
{
    if(newPosition != _position) {
        cv::Point2f tmpPosition = _position;
        _position = newPosition;
        emit positionChanged(this, tmpPosition, _position);
    }
}

float Card::rotation() const
{
    return _rotation;
}

void Card::setRotation(float newRotation)
{
    if (newRotation != _rotation) {
        float tmpRotation = _rotation;
        _rotation = newRotation;
        emit rotationChanged(this, tmpRotation, _rotation);
    }
}

QDebug operator<< (QDebug d, const Card &card)
{
    d<< "Card - c: " << card.color()
     << "- position x:" << card.position().x << " y: " << card.position().y;
    return d;
}

