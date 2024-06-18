#include "GameDataExtractor.h"
#include <iostream>

GameDataExtractor::GameDataExtractor(const std::string& dbPath)
    : dbHandler(dbPath) {}

void GameDataExtractor::extractData() {
    extractActionsData();
    extractPlayerData();
    extractAbilitiesData();
    // Add more extraction methods as needed
}

void GameDataExtractor::extractActionsData() {
    std::string query = "SELECT ActionID, ActionName, Description FROM Actions";
    if (dbHandler.prepareStatement(query)) {
        while (dbHandler.step()) {
            int actionID = std::stoi(dbHandler.getColumnText(0));
            std::string actionName = dbHandler.getColumnText(1);
            std::string description = dbHandler.getColumnText(2);
            std::cout << "ActionID: " << actionID << ", ActionName: " << actionName << ", Description: " << description << std::endl;
        }
        dbHandler.finalizeStatement();
    }
}

void GameDataExtractor::extractPlayerData() {
    std::string query = "SELECT PlayerId, PlayerName, Email, CreatedAt FROM Player";
    if (dbHandler.prepareStatement(query)) {
        while (dbHandler.step()) {
            int playerId = std::stoi(dbHandler.getColumnText(0));
            std::string playerName = dbHandler.getColumnText(1);
            std::string email = dbHandler.getColumnText(2);
            std::string createdAt = dbHandler.getColumnText(3);
            std::cout << "PlayerId: " << playerId << ", PlayerName: " << playerName << ", Email: " << email << ", CreatedAt: " << createdAt << std::endl;
        }
        dbHandler.finalizeStatement();
    }
}

void GameDataExtractor::extractAbilitiesData() {
    std::string query = "SELECT AbilityID, AbilityName, AbilityType, Power, Cooldown, Description FROM Abilities";
    if (dbHandler.prepareStatement(query)) {
        while (dbHandler.step()) {
            int abilityID = std::stoi(dbHandler.getColumnText(0));
            std::string abilityName = dbHandler.getColumnText(1);
            int abilityType = std::stoi(dbHandler.getColumnText(2));
            int power = dbHandler.getColumnText(3) ? std::stoi(dbHandler.getColumnText(3)) : 0;
            int cooldown = dbHandler.getColumnText(4) ? std::stoi(dbHandler.getColumnText(4)) : 0;
            std::string description = dbHandler.getColumnText(5);
            std::cout << "AbilityID: " << abilityID << ", AbilityName: " << abilityName << ", AbilityType: " << abilityType << ", Power: " << power << ", Cooldown: " << cooldown << ", Description: " << description << std::endl;
        }
        dbHandler.finalizeStatement();
    }
}
