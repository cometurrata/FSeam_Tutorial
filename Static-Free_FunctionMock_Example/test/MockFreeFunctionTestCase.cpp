#include <catch2/catch.hpp>
#include <FSeamMockData.hpp>
#include "../include/ClassToTest.hh"

TEST_CASE("FreeFunction") {

    ClassToTest testingClass;
    auto mockFreeFunctions = FSeam::getFreeFunc();

    mockFreeFunctions->dupeReturn<FSeam::FreeFunction::generateRandomNumber>(42);

    SECTION("Check return value") {

        REQUIRE(testingClass.isFavoriteNumber(42));
        REQUIRE_FALSE(testingClass.isFavoriteNumber(-1));
        REQUIRE_FALSE(testingClass.isFavoriteNumber(1337));
        REQUIRE_FALSE(testingClass.isFavoriteNumber(16));


        SECTION("Check number of time called") {

            REQUIRE_FALSE(mockFreeFunctions->verify(FSeam::FreeFunction::generateRandomNumber::NAME, FSeam::NeverCalled{}, false));
            REQUIRE(mockFreeFunctions->verify(FSeam::FreeFunction::generateRandomNumber::NAME, 4));

        } // End section : Check number of time called

    } // End section : Check return value

    FSeam::MockVerifier::cleanUp();
} // End TestCase : FreeFunction