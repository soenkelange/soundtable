#ifndef CARD_H
#define CARD_H

#include <opencv2/opencv.hpp>
#include <QObject>
#include <QDebug>

class Card : public QObject
{
    Q_OBJECT

public:
    enum Color {
        RED,
        YELLOW,
        BLUE,
        GREEN
    };
    enum Shape {
        SQUARE,
        STAR,
        CIRCLE,
        TRIANGLE
    };

    Card(Color color, Shape shape);
    ~Card();

    Color color() const;
    Shape shape() const;

    cv::Point2f position() const;
    void setPosition(cv::Point2f newPosition);
    float rotation() const;
    void setRotation(float newRotation);

signals:
    void positionChanged(const Card *card, cv::Point2f oldPosition, cv::Point2f newPosition);
    void rotationChanged(const Card *card, float oldRotation, float newRotation);

private:
    Color _color;
    Shape _shape;
    cv::Point2f _position;
    float _rotation;
};

QDebug operator<< ( QDebug os, const Card &card );

#endif // CARD_H
