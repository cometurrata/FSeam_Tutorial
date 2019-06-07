#include <catch.hpp>
#include <vector>
#include <FSeamMockData.hpp>
#include "ClassToTest.hh"

using namespace FSeam;

TEST_CASE("Test Mocking default behavior on class") {

    // Create the TestingClass
    ClassToTest testingClass;

    // Get the default mock for the class ClassToTest
    auto fseamMock = FSeam::getDefault<::GameOfThronesDatabase>();

    SECTION("Check number of time called") {
        fseamMock->dupeReturn<FSeam::GameOfThronesDatabase::isPlayerWinnerOfGameOfThrones>(true);
        REQUIRE(testingClass.isWinnerOfGameOfThrones("The Broken"));
        fseamMock->dupeReturn<FSeam::GameOfThronesDatabase::isPlayerWinnerOfGameOfThrones>(false);
        REQUIRE_FALSE(testingClass.isWinnerOfGameOfThrones("Not knowledgeable guy"));
        REQUIRE_FALSE(testingClass.isWinnerOfGameOfThrones("Dragon girl"));        
        REQUIRE_FALSE(testingClass.isWinnerOfGameOfThrones("Wolf girl"));

        // Because this was quite unnexpected, we had 4 tries before finding the correct answer
        REQUIRE(fseamMock->verify(FSeam::GameOfThronesDatabase::isPlayerWinnerOfGameOfThrones::NAME, 4));
    }

    SECTION("Check argument on call") {
        // We check that at least 1 call has been done to isPlayerWinnerOfGameOfThrones with "The Broken" as parameter 
        fseamMock->expectArg<FSeam::GameOfThronesDatabase::isPlayerWinnerOfGameOfThrones>(Eq(std::string("The Broken")));
        // We check that exactly 3 call has been done to isPlayerWinnerOfGameOfThrones with "Not knowledgeable guy" as parameter 
        fseamMock->expectArg<FSeam::GameOfThronesDatabase::isPlayerWinnerOfGameOfThrones>(Eq(std::string("Not knowledgeable guy")), VerifyCompare{3});
        // We check that isPlayerWinnerOfGameOfThrones with "LittleFinger" as parameter has never been called
        fseamMock->expectArg<FSeam::GameOfThronesDatabase::isPlayerWinnerOfGameOfThrones>(Eq(std::string("LittleFinger")), NeverCalled{});

        fseamMock->dupeReturn<FSeam::GameOfThronesDatabase::isPlayerWinnerOfGameOfThrones>(false);
        REQUIRE_FALSE(testingClass.isWinnerOfGameOfThrones("Not knowledgeable guy"));
        REQUIRE_FALSE(testingClass.isWinnerOfGameOfThrones("Not knowledgeable guy"));        
        REQUIRE_FALSE(testingClass.isWinnerOfGameOfThrones("Not knowledgeable guy"));
        fseamMock->dupeReturn<FSeam::GameOfThronesDatabase::isPlayerWinnerOfGameOfThrones>(true);
        REQUIRE(testingClass.isWinnerOfGameOfThrones("The Broken"));

        REQUIRE(fseamMock->verify(FSeam::GameOfThronesDatabase::isPlayerWinnerOfGameOfThrones::NAME)); // verify expectations
       
    }

    FSeam::MockVerifier::cleanUp();
}
