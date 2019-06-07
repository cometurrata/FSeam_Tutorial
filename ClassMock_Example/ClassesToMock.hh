#pragma once

#include <vector>
#include <string>

class GameOfThronesDatabase {
public:
    bool isPlayerWinnerOfGameOfThrones(const std::string &name);

    std::vector<int> getGoodSeasons(int season);
    std::vector<int> getNotSoGoodSeasons(int season);

};
