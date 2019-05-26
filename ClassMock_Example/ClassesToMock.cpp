#include <ClassesToMock.hh>

bool GamesOfThronesDatabase::isPlayerWinnerOfGamesOfThrones(const std::string &player) {
    // imagine a db connection
    return true;
}

std::vector<int> GamesOfThronesDatabase::getNotSoGoodSeasons(int season) {
    // imagine a db connection
    return {42, 1337};
}

std::vector<int> GamesOfThronesDatabase::getGoodSeasons(int season) {
    // imagine a db connection
    return {1, 2, 3, 4};
}
