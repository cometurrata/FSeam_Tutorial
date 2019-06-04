#include <catch.hpp>
#include <vector>
#include <FSeamMockData.hpp>
#include "ClassToTest.hh"

using namespace FSeam;

TEST_CASE("Test Mocking default behavior on class") {

    // Create the TestingClass
    ClassToTest testingClass;

    // Get the default mock for the class ClassToTest
    auto fseamMock = FSeam::getDefault<::GamesOfThroneDatabase>();

    SECTION("Check number of time called") {
        fseamMock->dupeReturn<FSeam::GamesOfThroneDatabase::isPlayerWinnerOfGamesOfThrone>(true);
        REQUIRE(testingClass.isWinnerOfGamesOfThrone("The Broken"));
        fseamMock->dupeReturn<FSeam::GamesOfThroneDatabase::isPlayerWinnerOfGamesOfThrone>(false);
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrone("Not knowledgeable guy"));
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrone("Dragon girl"));        
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrone("Wolf girl"));

        // Because this was quite unnexpected, we had 4 tries before finding the correct answer
        REQUIRE(fseamMock->verify(FSeam::GamesOfThroneDatabase::isPlayerWinnerOfGamesOfThrone::NAME, 4));
    }

    SECTION("Check argument on call") {
        // We check that at least 1 call has been done to isPlayerWinnerOfGamesOfThrone with "The Broken" as parameter 
        fseamMock->expectArg<FSeam::GamesOfThroneDatabase::isPlayerWinnerOfGamesOfThrone>(Eq(std::string("The Broken")));
        // We check that exactly 3 call has been done to isPlayerWinnerOfGamesOfThrone with "Not knowledgeable guy" as parameter 
        fseamMock->expectArg<FSeam::GamesOfThroneDatabase::isPlayerWinnerOfGamesOfThrone>(Eq(std::string("Not knowledgeable guy")), VerifyCompare{3});
        // We check that isPlayerWinnerOfGamesOfThrone with "LittleFinger" as parameter has never been called
        fseamMock->expectArg<FSeam::GamesOfThroneDatabase::isPlayerWinnerOfGamesOfThrone>(Eq(std::string("LittleFinger")), NeverCalled{});

        fseamMock->dupeReturn<FSeam::GamesOfThroneDatabase::isPlayerWinnerOfGamesOfThrone>(false);
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrone("Not knowledgeable guy"));
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrone("Not knowledgeable guy"));        
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrone("Not knowledgeable guy"));
        fseamMock->dupeReturn<FSeam::GamesOfThroneDatabase::isPlayerWinnerOfGamesOfThrone>(true);
        REQUIRE(testingClass.isWinnerOfGamesOfThrone("The Broken"));

        REQUIRE(fseamMock->verify(FSeam::GamesOfThroneDatabase::isPlayerWinnerOfGamesOfThrone::NAME)); // verify expectations
       
    }

    FSeam::MockVerifier::cleanUp();
}
