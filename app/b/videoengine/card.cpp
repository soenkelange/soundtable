#include "card.h"

Card::Card(Color color, Shape shape) :
    _listener(0),
    _color(color),
    _shape(shape),
    _position(0,0)
{
    _visible = false;
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

void Card::setPosition(cv::Point2f position)
{
    if(position != _position) {
        cv::Point2f oldPosition = _position;
        _position = position;
        if (_listener != 0) {
            _listener->positionChanged(*this, oldPosition);
        }
    }
}

float Card::rotation() const
{
    return _rotation;
}

void Card::setRotation(float rotation)
{
    if(rotation != _rotation) {
        float oldRotation = _rotation;
        _rotation = rotation;
        if (_listener != 0) {
            _listener->rotationChanged(*this, oldRotation);
        }
    }
}

bool Card::isVisible() const
{
    return _visible;
}

void Card::setVisibility(bool visible)
{
    if(visible != _visible) {
        _visible = visible;
        if (_listener != 0) {
            _listener->visibilityChanged(*this);
        }
    }
}

void Card::setListener(CardEventListener *listener)
{
    _listener = listener;
}

void Card::removeListener()
{
    _listener = 0;
}

