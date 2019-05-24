#include <algorithm>
#include <ClassesToMock.hh>

class ClassToTest {
    
public:
    bool isWinnerOfGamesOfThrones(const std::string &name) {
        GamesOfThronesDatabase databaseConnectionHandler; // A new database connection is created out of the blue
        return databaseConnectionHandler.isPlayerWinnerOfGamesOfThrones(name);
    }

    bool isGoodGamesOfThroneSeason(int season) {
        std::vector<int> goodSeason = _db1.getGoodSeasons(season);
        std::vector<int> underwhelmingSeason = _db2.getNotSoGoodSeasons(season);

        if (std::find_first_of(goodSeason.begin(), goodSeason.end(), underwhelmingSeason.begin(), underwhelmingSeason.end()) != goodSeason.end())
            throw std::string("Database incoherency");
        if (std::find(goodSeason.begin(), goodSeason.end(), season))
            return true;
        if (std::find(underwhelmingSeason.begin(), underwhelmingSeason.end(), season))
            return false;    
        throw std::string("The season is not referenced");        
    }

    GamesOfThronesDatabase &getDb1() { return _db1; }
    GamesOfThronesDatabase &getDb2() { return _db2; }

private:
    GamesOfThronesDatabase _db1; 
    GamesOfThronesDatabase _db2;
};
