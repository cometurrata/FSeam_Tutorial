#include <catch.hpp>
#include <FSeamMockData.hpp>
#include "../include/ClassToTest.hh"

TEST_CASE("StaticFunction") {

    ClassToTest testingClass;
    auto mockStaticFunctions = FSeam::getFreeFunc(); // static functions are considered as free functions

    SECTION("Check call") {
        mockStaticFunctions->dupeReturn<FSeam::FreeFunction::getAllGames>(std::vector<std::string>({"FyS", "SC2"}));
        mockStaticFunctions->dupeReturn<FSeam::FreeFunction::getFavoriteGameForUser>(std::vector<std::string>({"SC2"}));

        REQUIRE(testingClass.isOneOfBestGameInTheWorld("UserName", "SC2"));
        REQUIRE_FALSE(testingClass.isOneOfBestGameInTheWorld("UserName", "FyS"));
        REQUIRE_FALSE(testingClass.isOneOfBestGameInTheWorld("UserName", "Warcraft3"));

        SECTION("Check number of time called") {

            REQUIRE(mockStaticFunctions->verify(FSeam::FreeFunction::getAllGames::NAME, 3));
            REQUIRE(mockStaticFunctions->verify(FSeam::FreeFunction::getFavoriteGameForUser::NAME, 3));

        } // End section : Check number of time called

        SECTION("Check arguments on call") {


        } // End section : Check arguments on call

    } // End section : Check call

    FSeam::MockVerifier::cleanUp();
} // End TestCase : StaticFunction