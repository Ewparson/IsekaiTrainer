#include "DatabaseHandler.h"
#include <iostream>
// Include your database library here, e.g., SQLite
// #include <sqlite3.h>

DatabaseHandler::DatabaseHandler(const std::string &dbPath) : dbPath(dbPath) {}

DatabaseHandler::~DatabaseHandler() {
    disconnect();
}

bool DatabaseHandler::connect() {
    // Implement database connection logic
    std::cout << "Connecting to database: " << dbPath << std::endl;
    return true;
}

bool DatabaseHandler::disconnect() {
    // Implement database disconnection logic
    std::cout << "Disconnecting from database: " << dbPath << std::endl;
    return true;
}

bool DatabaseHandler::executeQuery(const std::string &query) {
    // Implement query execution logic
    std::cout << "Executing query: " << query << std::endl;
    return true;
}

std::vector<std::vector<std::string>> DatabaseHandler::fetchResults(const std::string &query) {
    // Implement fetch results logic
    std::cout << "Fetching results for query: " << query << std::endl;
    return {};
}

#include "DatabaseHandler.h"
#include <iostream>

DatabaseHandler::DatabaseHandler(const std::string& dbName) : dbName(dbName), db(nullptr) {
    open();
}

DatabaseHandler::~DatabaseHandler() {
    close();
}

bool DatabaseHandler::open() {
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

void DatabaseHandler::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool DatabaseHandler::executeQuery(const std::string& query) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

std::vector<std::vector<std::string>> DatabaseHandler::getQueryResult(const std::string& query) {
    std::vector<std::vector<std::string>> results;
    char* errMsg = nullptr;
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        int cols = sqlite3_column_count(stmt);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::vector<std::string> row;
            for (int col = 0; col < cols; col++) {
                row.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, col)));
            }
            results.push_back(row);
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(db) << std::endl;
    }
    return results;
}
