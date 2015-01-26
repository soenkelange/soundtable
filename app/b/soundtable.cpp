#include "soundtable.h"

SoundTable::SoundTable() :
    _soundEngine(new SoundEngine),
    _cardsProcessor(new CardsProcessor)
{

}

SoundTable::~SoundTable()
{
    delete _soundEngine;
    delete _cardsProcessor;
}

SoundEngine* SoundTable::soundEngine() const
{
    return _soundEngine;
}

CardsProcessor* SoundTable::cardProcessor() const
{
    return _cardsProcessor;
}

