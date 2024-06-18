#include "MyGameProjectGameMode.h"
#include "APIManager.h"
#include "Engine/World.h"

void AMyGameProjectGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Find the APIManager actor in the world
    for (TActorIterator<AAPIManager> It(GetWorld()); It; ++It)
    {
        AAPIManager* APIManager = *It;
        if (APIManager)
        {
            APIManager->GetPlayerData();
            break;
        }
    }
}
