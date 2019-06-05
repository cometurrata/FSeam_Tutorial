#pragma once

#include <algorithm>
#include <vector>
#include <ClassesToMock.hh>

class ClassToTest {
    
public:
    bool isWinnerOfGameOfThrone(const std::string &name) {
        GameOfThroneDatabase databaseConnectionHandler; // A new database connection is created out of the blue
        return databaseConnectionHandler.isPlayerWinnerOfGameOfThrone(name);
    }

    bool isGoodGameOfThroneSeason(int season) {
        std::vector<int> goodSeason = _dbCouchbase.getGoodSeasons(season);
        std::vector<int> underwhelmingSeason = _dbCouchbase.getNotSoGoodSeasons(season);

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

    GameOfThroneDatabase &getDbSql() { return _dbSql; }
    GameOfThroneDatabase &getDbCouchbase() { return _dbCouchbase; }

private:
    GameOfThroneDatabase _dbSql;
    GameOfThroneDatabase _dbCouchbase;
};
