#include "DatabaseHandler.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"

bool UDatabaseHandler::ExportPlayerDataToJson(const TArray<FPlayerData>& PlayerDataArray)
{
    FString OutputString;
    FJsonObjectConverter::UStructArrayToJsonObjectString(PlayerDataArray, OutputString);

    FString FilePath = FPaths::ProjectDir() + "/Saved/PlayerData.json";
    return FFileHelper::SaveStringToFile(OutputString, *FilePath);
}

bool UDatabaseHandler::ExportGameDataToJson(const TArray<FGameData>& GameDataArray)
{
    FString OutputString;
    FJsonObjectConverter::UStructArrayToJsonObjectString(GameDataArray, OutputString);

    FString FilePath = FPaths::ProjectDir() + "/Saved/GameData.json";
    return FFileHelper::SaveStringToFile(OutputString, *FilePath);
}
