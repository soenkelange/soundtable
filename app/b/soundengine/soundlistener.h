#ifndef SOUNDLISTENER_H
#define SOUNDLISTENER_H

#include <irrKlang.h>

class SoundListener
{

private:
    class SoundListenerEventListener *_listener;

public:
    SoundListener(SoundListenerEventListener *listener);
    ~SoundListener();

    irrklang::vec3df position() const;
    void setPosition(irrklang::vec3df position);
    irrklang::vec3df lookDirection() const;
    void setLookDirection(irrklang::vec3df direction);
    irrklang::vec3df upVector() const;
    void setUpVector(irrklang::vec3df upVector);private:

private:
    irrklang::vec3df _position;
    irrklang::vec3df _lookDirection;
    irrklang::vec3df _upVector;

};

class SoundListenerEventListener
{
public:
    virtual ~SoundListenerEventListener() {}
    virtual void positionChanged() = 0;
    virtual void lookDirectionChanged() = 0;
    virtual void upVectorChanged() = 0;

};

#endif // SOUNDLISTENER_H

