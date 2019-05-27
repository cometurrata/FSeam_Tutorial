#include <catch.hpp>
#include <vector>
#include <FSeamMockData.hpp>
#include "ClassToTest.hh"

using namespace FSeam;

TEST_CASE("Class Mock Specific Instance") {

    // Create the TestingClass
    ClassToTest testingClass;

    // Get the mock instances
    auto fseamMock_SqlDatabase = FSeam::get(&testingClass.getDbSql());
    auto fseamMock_CoucheBase = FSeam::get(&testingClass.getDbCouchebase());
    
    SECTION("Test CoucheBase without duping SQL") {

        // Couchebase return values
        fseamMock_CoucheBase->dupeReturn<FSeam::ClassToTest::getGoodSeasons>(std::vector<int>({1,2,3,4,5,6}));
        fseamMock_CoucheBase->dupeReturn<FSeam::ClassToTest::getNotSoGoodSeasons>(std::vector<int>({7,8}));

        REQUIRE(testingClass.isGoodGamesOfThroneSeason(1));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(2));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(3));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(4));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(5));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(6));

        REQUIRE_FALSE(testingClass.isGoodGamesOfThroneSeason(7));
        REQUIRE_FALSE(testingClass.isGoodGamesOfThroneSeason(8));

        // Check fseamMock_CoucheBase has been called 8 times (for both methods)
        REQUIRE(fseamMock_CoucheBase->verify(FSeam::ClassToTest::getGoodSeasons, 8));
        REQUIRE(fseamMock_CoucheBase->verify(FSeam::ClassToTest::getNotSoGoodSeasons, 8));
        // Because data are present in the cache, SQL connector is never called
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::ClassToTest::getGoodSeasons, FSeam::NeverCalled{}));
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::ClassToTest::getNotSoGoodSeasons, FSeam::NeverCalled{}));
    }

    SECTION("Test Couchebase (goodSeason) and SQL (badSeason)") {
        
        // Couchebase will return goodSeasons, SQL will return bad seasons
        fseamMock_CoucheBase->dupeReturn<FSeam::ClassToTest::getGoodSeasons>(std::vector<int>({1,2,3,4,5,6}));
        fseamMock_SqlDatabase->dupeReturn<FSeam::ClassToTest::getNotSoGoodSeasons>(std::vector<int>({7,8}));

        REQUIRE(testingClass.isGoodGamesOfThroneSeason(1));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(2));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(3));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(4));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(5));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(6));

        REQUIRE_FALSE(testingClass.isGoodGamesOfThroneSeason(7));
        REQUIRE_FALSE(testingClass.isGoodGamesOfThroneSeason(8));

        REQUIRE(fseamMock_CoucheBase->verify(FSeam::ClassToTest::getGoodSeasons, 8));
        REQUIRE(fseamMock_CoucheBase->verify(FSeam::ClassToTest::getNotSoGoodSeasons, 8));
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::ClassToTest::getNotSoGoodSeasons, 8));
        // Because data are present in the cache, getGoodSeasons is never called for SQL
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::ClassToTest::getGoodSeasons, FSeam::NeverCalled{}));
    }

    SECTION("Test Couchebase (badSeason) and SQL (goodSeason)") {
        
        // Couchebase will return goodSeasons, SQL will return bad seasons
        fseamMock_CoucheBase->dupeReturn<FSeam::ClassToTest::getNotSoGoodSeasons>(std::vector<int>({7,8}));
        fseamMock_SqlDatabase->dupeReturn<FSeam::ClassToTest::getGoodSeasons>(std::vector<int>({1,2,3,4,5,6}));

        REQUIRE(testingClass.isGoodGamesOfThroneSeason(1));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(2));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(3));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(4));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(5));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(6));

        REQUIRE_FALSE(testingClass.isGoodGamesOfThroneSeason(7));
        REQUIRE_FALSE(testingClass.isGoodGamesOfThroneSeason(8));

        REQUIRE(fseamMock_CoucheBase->verify(FSeam::ClassToTest::getGoodSeasons, 8));
        REQUIRE(fseamMock_CoucheBase->verify(FSeam::ClassToTest::getNotSoGoodSeasons, 8));
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::ClassToTest::getGoodSeasons, 8));
        // Because data are present in the cache, getNotSoGoodSeasons is never called for SQL
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::ClassToTest::getNotSoGoodSeasons, FSeam::NeverCalled{}));
    }

    SECTION("Test database incoherency") {
        fseamMock_CoucheBase->dupeReturn<FSeam::ClassToTest::getGoodSeasons>(std::vector<int>({1,2,3,4,5,6}));
        fseamMock_CoucheBase->dupeReturn<FSeam::ClassToTest::getNotSoGoodSeasons>(std::vector<int>({1,2,3,4,5,6}));
        
        REQUIRE_THROWS(testingClass.isGoodGamesOfThroneSeason(1));
        
        // Because data are present in the cache, SQL connector is never called
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::ClassToTest::getGoodSeasons, FSeam::NeverCalled{}));
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::ClassToTest::getNotSoGoodSeasons, FSeam::NeverCalled{}));
    }

    SECTION("Test undefined season") {
        fseamMock_CoucheBase->dupeReturn<FSeam::ClassToTest::getGoodSeasons>(std::vector<int>({1,2,3,4,5,6}));
        fseamMock_CoucheBase->dupeReturn<FSeam::ClassToTest::getNotSoGoodSeasons>(std::vector<int>({8}));
        
        REQUIRE_THROWS(testingClass.isGoodGamesOfThroneSeason(7));
        
        // Because data are present in the cache, SQL connector is never called
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::ClassToTest::getGoodSeasons, FSeam::NeverCalled{}));
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::ClassToTest::getNotSoGoodSeasons, FSeam::NeverCalled{}));
    }


}
