#include <vector>

class DatabaseAccessor {
public:
    static std::vector<std::string> getAllGames();
    static std::vector<std::string> getFavoriteGameForUser(const std::string &user, const std::string &game);

};
