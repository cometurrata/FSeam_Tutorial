#include <catch.hpp>
#include <vector>
#include <FSeamMockData.hpp>
#include "ClassToTest.hh"

using namespace FSeam;

TEST_CASE("Test Mocking default behavior on class") {

    // Create the TestingClass
    ClassToTest testingClass;

    // Get the default mock for the class ClassToTest
    auto fseamMock = FSeam::getDefault<::GameOfThroneDatabase>();

    SECTION("Check number of time called") {
        fseamMock->dupeReturn<FSeam::GameOfThroneDatabase::isPlayerWinnerOfGameOfThrone>(true);
        REQUIRE(testingClass.isWinnerOfGameOfThrone("The Broken"));
        fseamMock->dupeReturn<FSeam::GameOfThroneDatabase::isPlayerWinnerOfGameOfThrone>(false);
        REQUIRE_FALSE(testingClass.isWinnerOfGameOfThrone("Not knowledgeable guy"));
        REQUIRE_FALSE(testingClass.isWinnerOfGameOfThrone("Dragon girl"));        
        REQUIRE_FALSE(testingClass.isWinnerOfGameOfThrone("Wolf girl"));

        // Because this was quite unnexpected, we had 4 tries before finding the correct answer
        REQUIRE(fseamMock->verify(FSeam::GameOfThroneDatabase::isPlayerWinnerOfGameOfThrone::NAME, 4));
    }

    SECTION("Check argument on call") {
        // We check that at least 1 call has been done to isPlayerWinnerOfGameOfThrone with "The Broken" as parameter 
        fseamMock->expectArg<FSeam::GameOfThroneDatabase::isPlayerWinnerOfGameOfThrone>(Eq(std::string("The Broken")));
        // We check that exactly 3 call has been done to isPlayerWinnerOfGameOfThrone with "Not knowledgeable guy" as parameter 
        fseamMock->expectArg<FSeam::GameOfThroneDatabase::isPlayerWinnerOfGameOfThrone>(Eq(std::string("Not knowledgeable guy")), VerifyCompare{3});
        // We check that isPlayerWinnerOfGameOfThrone with "LittleFinger" as parameter has never been called
        fseamMock->expectArg<FSeam::GameOfThroneDatabase::isPlayerWinnerOfGameOfThrone>(Eq(std::string("LittleFinger")), NeverCalled{});

        fseamMock->dupeReturn<FSeam::GameOfThroneDatabase::isPlayerWinnerOfGameOfThrone>(false);
        REQUIRE_FALSE(testingClass.isWinnerOfGameOfThrone("Not knowledgeable guy"));
        REQUIRE_FALSE(testingClass.isWinnerOfGameOfThrone("Not knowledgeable guy"));        
        REQUIRE_FALSE(testingClass.isWinnerOfGameOfThrone("Not knowledgeable guy"));
        fseamMock->dupeReturn<FSeam::GameOfThroneDatabase::isPlayerWinnerOfGameOfThrone>(true);
        REQUIRE(testingClass.isWinnerOfGameOfThrone("The Broken"));

        REQUIRE(fseamMock->verify(FSeam::GameOfThroneDatabase::isPlayerWinnerOfGameOfThrone::NAME)); // verify expectations
       
    }

    FSeam::MockVerifier::cleanUp();
}
