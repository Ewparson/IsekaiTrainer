#include "GameDataExtractor.h"
#include "DatabaseHandler.h"
#include <iostream>

int main() {
    GameDataExtractor extractor("data.txt");
    std::vector<std::string> data = extractor.extractData();

    DatabaseHandler dbHandler("gameData.db");
    dbHandler.executeQuery("CREATE TABLE IF NOT EXISTS gameData (id INTEGER PRIMARY KEY, line TEXT);");

    for (const auto& line : data) {
        std::string query = "INSERT INTO gameData (line) VALUES ('" + line + "');";
        dbHandler.executeQuery(query);
    }

    std::vector<std::vector<std::string>> results = dbHandler.getQueryResult("SELECT * FROM gameData;");
    for (const auto& row : results) {
        for (const auto& col : row) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
