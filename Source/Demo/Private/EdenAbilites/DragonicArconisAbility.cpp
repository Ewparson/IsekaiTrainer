#include "DraconicArcanisAbility.h"
#include "DatabaseHandler.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"

UDraconicArcanisAbility::UDraconicArcanisAbility()
{
    // Set the ability to be triggered by an input action
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDraconicArcanisAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (ActorInfo->OwnerActor)
    {
        // Implement your ability logic here, such as spawning effects or dealing damage
        UE_LOG(LogTemp, Warning, TEXT("Draconic Arcanis Activated!"));

        // End the ability (for instant abilities)
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
    }
}
