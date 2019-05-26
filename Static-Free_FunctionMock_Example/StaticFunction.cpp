 #include <StaticFunction.hh>


 std::vector<std::string> DatabaseAccessor::getAllGames() {
     // Imagine singleton access to a database
     return {"StarcraftII", "WarcraftIII", "Tales Of Symphonia", "FreeYourSoulMMORPG", "Final Fantasy"};
 }

 std::vector<std::string> DatabaseAccessor::getFavoriteGameForUser(const std::string &user, const std::string &game) {
     // Again, try to use your imagination;
     return {"Game1", "Game2", "Game3"};
 }
