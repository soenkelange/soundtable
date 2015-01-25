#include "card.h"

Card::Card(Color color, Shape shape) :
    _listener(0),
    _color(color),
    _shape(shape),
    _position(0,0),
    _rotation(0),
    _visible(false),
    _detected(false)
{
}

Card::~Card()
{

}

Card::Color Card::color() const
{
    return _color;
}

cv::Scalar Card::colorAsScalar() const
{
    switch(_color) {
    case Card::Yellow:
        return cv::Scalar(0,255,255);
    case Card::Red:
        return cv::Scalar(0,0,255);
    case Card::Blue:
        return cv::Scalar(255,0,0);
    }
}

QString Card::colorName() const
{
    switch(_color) {
    case Card::Yellow:
        return "Yellow";
    case Card::Red:
        return "Red";
    case Card::Blue:
        return "Blue";
    }
}

Card::Shape Card::shape() const
{
    return _shape;
}

QString Card::shapeName() const
{
    switch(_shape) {
    case Card::Triangle:
        return "Triangle";
    case Card::Square:
        return "Square";
    case Card::Hexagon:
        return "Hexagon";
    case Card::Circle:
        return "Circle";
    case Card::Star:
        return "Star";
    }
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

bool Card::isDetected() const
{
    return _detected;
}

void Card::setDetected(bool detected)
{
    _detected = detected;
}

void Card::setListener(CardEventListener *listener)
{
    _listener = listener;
}

void Card::removeListener()
{
    _listener = 0;
}

QDebug operator <<(QDebug os, const Card &card) {
    os << "Card - color: " << card.colorName()
       << " shape: " << card.shapeName()
       << " position: (" << card.position().x << "," << card.position().y << ")"
       << " visiblity: " << card.isVisible()
       << " detected: " << card.isDetected()
       << " rotation:" << card.rotation();
    return os;
}

