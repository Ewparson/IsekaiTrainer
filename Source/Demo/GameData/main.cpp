#include "GameDataExtractor.h"

int main() {
    std::string dbPath = "isekai_trainer_database.db";
    GameDataExtractor extractor(dbPath);
    extractor.extractData();
    return 0;
}
