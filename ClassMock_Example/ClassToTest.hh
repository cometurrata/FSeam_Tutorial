#pragma once

#include <algorithm>
#include <vector>
#include <ClassesToMock.hh>

class ClassToTest {
    
public:
    bool isWinnerOfGamesOfThrones(const std::string &name) {
        GamesOfThronesDatabase databaseConnectionHandler; // A new database connection is created out of the blue
        return databaseConnectionHandler.isPlayerWinnerOfGamesOfThrones(name);
    }

    bool isGoodGamesOfThroneSeason(int season) {
        std::vector<int> goodSeason = _dbCouchebase.getGoodSeasons(season);
        std::vector<int> underwhelmingSeason = _dbCouchebase.getNotSoGoodSeasons(season);

        if (goodSeason.empty()) {
            goodSeason = _dbSql.getGoodSeasons(season);
        }
        if (underwhelmingSeason.empty()) {
            underwhelmingSeason = _dbSql.getNotSoGoodSeasons(season);
        }

        if (std::find_first_of(goodSeason.begin(), goodSeason.end(), underwhelmingSeason.begin(),
                underwhelmingSeason.end()) != goodSeason.end()) {
            std::cerr << "Database incoherency\n";
            throw std::string("Database incoherency");
        }
        if (std::find(goodSeason.begin(), goodSeason.end(), season) != goodSeason.end())
            return true;
        if (std::find(underwhelmingSeason.begin(), underwhelmingSeason.end(), season) != underwhelmingSeason.end())
            return false;
        std::cerr << "The season is not referenced\n";
        throw std::string("The season is not referenced");
    }

    GamesOfThronesDatabase &getDbSql() { return _dbSql; }
    GamesOfThronesDatabase &getDbCouchebase() { return _dbCouchebase; }

private:
    GamesOfThronesDatabase _dbSql;
    GamesOfThronesDatabase _dbCouchebase;
};
