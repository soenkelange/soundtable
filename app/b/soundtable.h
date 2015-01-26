#ifndef SOUNDTABLE_H
#define SOUNDTABLE_H

#include "soundengine/soundengine.h"
#include "videoengine/cardsprocessor.h"

class SoundTable
{
public:
    SoundTable();
    ~SoundTable();

    SoundEngine* soundEngine() const;
    CardsProcessor* cardProcessor() const;

private:
    SoundEngine *_soundEngine;
    CardsProcessor *_cardsProcessor;
};

#endif // SOUNDTABLE_H
