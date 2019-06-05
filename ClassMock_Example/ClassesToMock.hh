#pragma once

#include <vector>
#include <string>

class GameOfThroneDatabase {
public:
    bool isPlayerWinnerOfGameOfThrone(const std::string &name);

    std::vector<int> getGoodSeasons(int season);
    std::vector<int> getNotSoGoodSeasons(int season);

};
