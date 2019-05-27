#include <catch.hpp>
#include <vector>
#include <FSeamMockData.hpp>
#include "ClassToTest.hh"

using namespace FSeam;

TEST_CASE("Test Mocking default behavior on class") {

    // Create the TestingClass
    ClassToTest testingClass;

    // Get the default mock for the class ClassToTest
    auto fseamMock = FSeam::getDefault<::GamesOfThronesDatabase>();

    SECTION("Check number of time called") {
        fseamMock->dupeReturn<FSeam::GamesOfThronesDatabase::isPlayerWinnerOfGamesOfThrones>(true);
        REQUIRE(testingClass.isWinnerOfGamesOfThrones("The Broken"));
        fseamMock->dupeReturn<FSeam::GamesOfThronesDatabase::isPlayerWinnerOfGamesOfThrones>(false);
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrones("Not knowledgeable guy"));
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrones("Dragon girl"));        
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrones("Wolf girl"));

        // Because this was quite unnexpected, we had 4 tries before finding the correct answer
        REQUIRE(fseamMock->verify(FSeam::GamesOfThronesDatabase::isPlayerWinnerOfGamesOfThrones::NAME, 4));
    }

    SECTION("Check argument on call") {
        // We check that at least 1 call has been done to isPlayerWinnerOfGamesOfThrones with "The Broken" as parameter 
        fseamMock->expectArg<FSeam::GamesOfThronesDatabase::isPlayerWinnerOfGamesOfThrones>(Eq(std::string("The Broken")));
        // We check that exactly 3 call has been done to isPlayerWinnerOfGamesOfThrones with "Not knowledgeable guy" as parameter 
        fseamMock->expectArg<FSeam::GamesOfThronesDatabase::isPlayerWinnerOfGamesOfThrones>(Eq(std::string("Not knowledgeable guy")), VerifyCompare{3});
        // We check that isPlayerWinnerOfGamesOfThrones with "LittleFinger" as parameter has never been called
        fseamMock->expectArg<FSeam::GamesOfThronesDatabase::isPlayerWinnerOfGamesOfThrones>(Eq(std::string("LittleFinger")), NeverCalled{});

        fseamMock->dupeReturn<FSeam::GamesOfThronesDatabase::isPlayerWinnerOfGamesOfThrones>(false);
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrones("Not knowledgeable guy"));
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrones("Not knowledgeable guy"));        
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrones("Not knowledgeable guy"));
        fseamMock->dupeReturn<FSeam::GamesOfThronesDatabase::isPlayerWinnerOfGamesOfThrones>(true);
        REQUIRE(testingClass.isWinnerOfGamesOfThrones("The Broken"));

        REQUIRE(fseamMock->verify(FSeam::GamesOfThronesDatabase::isPlayerWinnerOfGamesOfThrones::NAME)); // verify expectations
       
    }

    FSeam::MockVerifier::cleanUp();
}
