#include "SlideOfHand.h"
#include "Character.h"
#include "InputHandler.h"

SlideOfHand::SlideOfHand() : Ability("Slide-Of-Hand") {}

void SlideOfHand::Execute(Character* character) {
    // Logic to cycle through weapons
    character->CycleWeaponsLeftHand();

    // Check if "Cycle Dragonic Arconis" is also held
    if (InputHandler::IsAbilityActive("Cycle Dragonic Arconis")) {
        character->CycleScrollAbilities();
    }
}
