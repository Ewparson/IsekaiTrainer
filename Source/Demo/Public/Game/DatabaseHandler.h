#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <string>
#include <vector>

class DatabaseHandler {
public:
    DatabaseHandler(const std::string &dbPath);
    ~DatabaseHandler();

    bool connect();
    bool disconnect();
    bool executeQuery(const std::string &query);
    std::vector<std::vector<std::string>> fetchResults(const std::string &query);

private:
    std::string dbPath;
    // Add database connection object here
};

#endif // DATABASEHANDLER_H
