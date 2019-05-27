#include <catch.hpp>
#include <vector>
#include <FSeamMockData.hpp>
#include "ClassToTest.hh"

using namespace FSeam;


TEST_CASE("Test Mocking default behavior on class") {

    // Create the TestingClass
    ClassToTest testingClass;

    // Get the default mock for the class ClassToTest
    auto fseamMock = FSeam::getDefault<ClassToTest>();

    fseamMock->dupeReturn<FSeam::ClassToTest::isPlayerWinnerOfGamesOfThrones>("The Broken");

    SECTION("Check number of time called") {
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrones("Not knowledgeable guy"));
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrones("Dragon girl"));        
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrones("Wolf girl"));
        REQUIRE(testingClass.isWinnerOfGamesOfThrones("The Broken"));

        // Because this was quite unnexpected, we had 4 tries before finding the correct answer
        REQUIRE(fseamMock->verify(FSeam::ClassToTest::isPlayerWinnerOfGamesOfThrones::NAME, 4));
    }

    SECTION("Check argument on call") {
        // We check that at least 1 call has been done to isPlayerWinnerOfGamesOfThrones with "The Broken" as parameter 
        fseamMock->expectArg<FSeam::ClassToTest::isPlayerWinnerOfGamesOfThrones>(Eq(std::string("The Broken")));
        // We check that exactly 3 call has been done to isPlayerWinnerOfGamesOfThrones with "Not knowledgeable guy" as parameter 
        fseamMock->expectArg<FSeam::ClassToTest::isPlayerWinnerOfGamesOfThrones>(Eq(std::string("Not knowledgeable guy"), VerifyCompare{3});
        // We check that isPlayerWinnerOfGamesOfThrones with "LittleFinger" as parameter has never been called
        fseamMock->expectArg<FSeam::ClassToTest::isPlayerWinnerOfGamesOfThrones>(Eq(std::string("LittleFinger"), NeverCalled{}));

        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrones("Not knowledgeable guy"));
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrones("Not knowledgeable guy"));        
        REQUIRE_FALSE(testingClass.isWinnerOfGamesOfThrones("Not knowledgeable guy"));
        REQUIRE(testingClass.isWinnerOfGamesOfThrones("The Broken"));

        REQUIRE(fseamMock->verify(FSeam::ClassToTest::isPlayerWinnerOfGamesOfThrones::NAME)); // verify expectations
       
    }

}
