#ifndef SOUNDTABLE_H
#define SOUNDTABLE_H

#include "soundengine/soundengine.h"
class SoundTable
{
public:
    SoundTable();
    ~SoundTable();

private:
    SoundEngine _soundEngine;
};

#endif // SOUNDTABLE_H
