#include "APIManager.h"
#include "Engine/Engine.h"

AAPIManager::AAPIManager()
{
    PrimaryActorTick.bCanEverTick = true;
    Http = &FHttpModule::Get();
}

void AAPIManager::BeginPlay()
{
    Super::BeginPlay();
}

void AAPIManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAPIManager::GetPlayerData()
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &AAPIManager::OnResponseReceived);
    Request->SetURL("https://api.example.com/players");
    Request->SetVerb("GET");
    Request->SetHeader("Content-Type", "application/json");
    Request->ProcessRequest();
}

void AAPIManager::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        FString ResponseString = Response->GetContentAsString();
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, ResponseString);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Request failed");
    }
}
