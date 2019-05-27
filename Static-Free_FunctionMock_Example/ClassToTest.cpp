#include <algorithm>
#include <FreeFunction.hh>
#include <StaticFunction.hh>
#include <iostream>
#include "include/ClassToTest.hh"

bool ClassToTest::isOneOfBestGameInTheWorld(const std::string &user, const std::string &game) {
    std::vector<std::string> games = DatabaseAccessor::getAllGames();
    if (games.empty())
        throw std::string("We live in a sad and cruel world without game :'(");
    std::vector<std::string> favoriteGames = DatabaseAccessor::getFavoriteGameForUser(user, game);
    if (favoriteGames.empty())
        throw std::string("Really?...");
    return std::find(favoriteGames.begin(), favoriteGames.end(), game) != favoriteGames.end();
}

bool ClassToTest::isFavoriteNumber(int number) {
    int random = generateRandomNumber();
    return number == random;
}