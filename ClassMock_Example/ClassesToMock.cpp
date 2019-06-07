#include <ClassesToMock.hh>

bool GameOfThronesDatabase::isPlayerWinnerOfGameOfThrones(const std::string &player) {
    // imagine a db connection
    return true;
}

std::vector<int> GameOfThronesDatabase::getNotSoGoodSeasons(int season) {
    // imagine a db connection
    return {42, 1337};
}

std::vector<int> GameOfThronesDatabase::getGoodSeasons(int season) {
    // imagine a db connection
    return {1, 2, 3, 4};
}
