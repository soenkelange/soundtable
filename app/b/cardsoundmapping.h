#ifndef CARDSOUNDMAPPING_H
#define CARDSOUNDMAPPING_H

#include "soundengine/soundsource.h"

class CardSoundMapping
{
public:
    CardSoundMapping();
    ~CardSoundMapping();

    void setSoundSource(SoundSource *soundSource);

private:
    SoundSource *source;
};

#endif // CARDSOUNDMAPPING_H
