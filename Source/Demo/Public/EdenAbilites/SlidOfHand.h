#ifndef SLIDE_OF_HAND_H
#define SLIDE_OF_HAND_H

#include "Ability.h"

class SlideOfHand : public Ability {
public:
    SlideOfHand();
    void Execute(Character* character) override;
};

#endif // SLIDE_OF_HAND_H
