#include <string>

class GamesOfThronesDatabase {
public:
    bool isPlayerWinnerOfGamesOfThrones(const std::string name);

    std::vector<int> getGoodSeasons(int season);
    std::vector<int> getNotSoGoodSeasons(int season);

}
