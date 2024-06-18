#include "GameDataExtractor.h"
#include <fstream>
#include <iostream>

GameDataExtractor::GameDataExtractor(const std::string &source) : source(source) {}

GameDataExtractor::~GameDataExtractor() {}

void GameDataExtractor::extractData() {
    // Implement extraction logic
    std::ifstream file(source);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << source << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }
    file.close();
    parseData();
}

std::vector<std::string> GameDataExtractor::getData() const {
    return data;
}

void GameDataExtractor::parseData() {
    // Implement parsing logic
}

