#ifndef SOUNDLISTENER_H
#define SOUNDLISTENER_H

#include <opencv2/opencv.hpp>

class SoundListener
{
public:
    SoundListener();
    ~SoundListener();

    cv::Point3f position() const;
    void setPosition(cv::Point3f position);
    cv::Point3f lookDirection() const;
    void setLookDirection(cv::Point3f direction);
    cv::Point3f upVector() const;
    void setUpVector(cv::Point3f upVector);

private:
    cv::Point3f _position;
    cv::Point3f _lookDirection;
    cv::Point3f _upVector;
};

#endif // SOUNDLISTENER_H
