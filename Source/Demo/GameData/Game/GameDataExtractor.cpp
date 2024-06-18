#ifndef GAMEDATAEXTRACTOR_H
#define GAMEDATAEXTRACTOR_H

#include <string>
#include <vector>

class GameDataExtractor {
public:
    GameDataExtractor(const std::string &source);
    ~GameDataExtractor();

    void extractData();
    std::vector<std::string> getData() const;

private:
    std::string source;
    std::vector<std::string> data;
    
    void parseData();
};

#endif // GAMEDATAEXTRACTOR_H
