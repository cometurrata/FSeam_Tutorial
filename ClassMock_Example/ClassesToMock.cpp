#include <ClassesToMock.hh>

bool GamesOfThroneDatabase::isPlayerWinnerOfGamesOfThrone(const std::string &player) {
    // imagine a db connection
    return true;
}

std::vector<int> GamesOfThroneDatabase::getNotSoGoodSeasons(int season) {
    // imagine a db connection
    return {42, 1337};
}

std::vector<int> GamesOfThroneDatabase::getGoodSeasons(int season) {
    // imagine a db connection
    return {1, 2, 3, 4};
}
