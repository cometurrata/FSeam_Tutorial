#include <ClassesToMock.hh>

bool GameOfThroneDatabase::isPlayerWinnerOfGameOfThrone(const std::string &player) {
    // imagine a db connection
    return true;
}

std::vector<int> GameOfThroneDatabase::getNotSoGoodSeasons(int season) {
    // imagine a db connection
    return {42, 1337};
}

std::vector<int> GameOfThroneDatabase::getGoodSeasons(int season) {
    // imagine a db connection
    return {1, 2, 3, 4};
}
