#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DragonicArcanisAction.generated.h"
#pragma once

#include "CoreMinimal.h"
// Other includes go here
#include "DatabaseHandler.h"

// Rest of the header file content


#include "DraconicArcanisAbility.generated.h"

UCLASS()
class DEMO_API UDraconicArcanisAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:5
    UDraconicArcanisAbility();

    // Override the activation method
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
