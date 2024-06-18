#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "APIManager.generated.h"

UCLASS()
class MYGAMEPROJECT_API AAPIManager : public AActor
{
    GENERATED_BODY()
    
public:    
    AAPIManager();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void Tick(float DeltaTime) override;

    void GetPlayerData();
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

private:
    FHttpModule* Http;
};
