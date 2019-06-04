#pragma once

#include <vector>
#include <string>

class GamesOfThroneDatabase {
public:
    bool isPlayerWinnerOfGamesOfThrone(const std::string &name);

    std::vector<int> getGoodSeasons(int season);
    std::vector<int> getNotSoGoodSeasons(int season);

};
