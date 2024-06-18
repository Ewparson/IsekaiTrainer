#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DatabaseHandler.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    int32 PlayerID;

    UPROPERTY(BlueprintReadWrite)
    FString Name;
};

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    int32 GameID;

    UPROPERTY(BlueprintReadWrite)
    int32 PlayerID;

    UPROPERTY(BlueprintReadWrite)
    int32 Score;
};

UCLASS()
class UDatabaseHandler : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Data")
    static bool ExportPlayerDataToJson(const TArray<FPlayerData>& PlayerDataArray);

    UFUNCTION(BlueprintCallable, Category = "Data")
    static bool ExportGameDataToJson(const TArray<FGameData>& GameDataArray);
};
