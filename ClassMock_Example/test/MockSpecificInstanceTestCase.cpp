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
    auto fseamMock_Couchbase = FSeam::get(&testingClass.getDbCouchbase());

    SECTION("Test Couchbase without duping SQL") {

        // Couchbase return values
        fseamMock_Couchbase->dupeReturn<FSeam::GamesOfThroneDatabase::getGoodSeasons>(std::vector<int>({1,2,3,4,5,6}));
        fseamMock_Couchbase->dupeReturn<FSeam::GamesOfThroneDatabase::getNotSoGoodSeasons>(std::vector<int>({7,8}));

        REQUIRE(testingClass.isGoodGamesOfThroneSeason(1));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(2));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(3));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(4));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(5));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(6));

        REQUIRE_FALSE(testingClass.isGoodGamesOfThroneSeason(7));
        REQUIRE_FALSE(testingClass.isGoodGamesOfThroneSeason(8));

        // Check fseamMock_Couchbase has been called 8 times (for both methods)
        REQUIRE(fseamMock_Couchbase->verify(FSeam::GamesOfThroneDatabase::getGoodSeasons::NAME, 8));
        REQUIRE(fseamMock_Couchbase->verify(FSeam::GamesOfThroneDatabase::getNotSoGoodSeasons::NAME, 8));
        // Because data are present in the cache, SQL connector is never called
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::GamesOfThroneDatabase::getGoodSeasons::NAME, FSeam::NeverCalled{}));
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::GamesOfThroneDatabase::getNotSoGoodSeasons::NAME, FSeam::NeverCalled{}));
    }

    SECTION("Test Couchbase (goodSeason) and SQL (badSeason)") {

        // Couchbase will return goodSeasons, SQL will return bad seasons
        fseamMock_Couchbase->dupeReturn<FSeam::GamesOfThroneDatabase::getGoodSeasons>(std::vector<int>({1,2,3,4,5,6}));
        fseamMock_SqlDatabase->dupeReturn<FSeam::GamesOfThroneDatabase::getNotSoGoodSeasons>(std::vector<int>({7,8}));

        REQUIRE(testingClass.isGoodGamesOfThroneSeason(1));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(2));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(3));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(4));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(5));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(6));

        REQUIRE_FALSE(testingClass.isGoodGamesOfThroneSeason(7));
        REQUIRE_FALSE(testingClass.isGoodGamesOfThroneSeason(8));

        REQUIRE(fseamMock_Couchbase->verify(FSeam::GamesOfThroneDatabase::getGoodSeasons::NAME, 8));
        REQUIRE(fseamMock_Couchbase->verify(FSeam::GamesOfThroneDatabase::getNotSoGoodSeasons::NAME, 8));
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::GamesOfThroneDatabase::getNotSoGoodSeasons::NAME, 8));
        // Because data are present in the cache, getGoodSeasons is never called for SQL
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::GamesOfThroneDatabase::getGoodSeasons::NAME, FSeam::NeverCalled{}));
    }

    SECTION("Test Couchbase (badSeason) and SQL (goodSeason)") {

        // Couchbase will return goodSeasons, SQL will return bad seasons
        fseamMock_Couchbase->dupeReturn<FSeam::GamesOfThroneDatabase::getNotSoGoodSeasons>(std::vector<int>({7,8}));
        fseamMock_SqlDatabase->dupeReturn<FSeam::GamesOfThroneDatabase::getGoodSeasons>(std::vector<int>({1,2,3,4,5,6}));

        REQUIRE(testingClass.isGoodGamesOfThroneSeason(1));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(2));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(3));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(4));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(5));
        REQUIRE(testingClass.isGoodGamesOfThroneSeason(6));

        REQUIRE_FALSE(testingClass.isGoodGamesOfThroneSeason(7));
        REQUIRE_FALSE(testingClass.isGoodGamesOfThroneSeason(8));

        REQUIRE(fseamMock_Couchbase->verify(FSeam::GamesOfThroneDatabase::getGoodSeasons::NAME, 8));
        REQUIRE(fseamMock_Couchbase->verify(FSeam::GamesOfThroneDatabase::getNotSoGoodSeasons::NAME, 8));
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::GamesOfThroneDatabase::getGoodSeasons::NAME, 8));
        // Because data are present in the cache, getNotSoGoodSeasons is never called for SQL
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::GamesOfThroneDatabase::getNotSoGoodSeasons::NAME, FSeam::NeverCalled{}));
    }

    SECTION("Test database incoherency") {
        fseamMock_Couchbase->dupeReturn<FSeam::GamesOfThroneDatabase::getGoodSeasons>(std::vector<int>({1,2,3,4,5,6}));
        fseamMock_Couchbase->dupeReturn<FSeam::GamesOfThroneDatabase::getNotSoGoodSeasons>(std::vector<int>({1,2,3,4,5,6}));

        REQUIRE_THROWS_WITH(testingClass.isGoodGamesOfThroneSeason(1), Catch::Contains("Database incoherency"));

        // Because data are present in the cache, SQL connector is never called
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::GamesOfThroneDatabase::getGoodSeasons::NAME, FSeam::NeverCalled{}));
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::GamesOfThroneDatabase::getNotSoGoodSeasons::NAME, FSeam::NeverCalled{}));
    }

    SECTION("Test undefined season") {
        fseamMock_Couchbase->dupeReturn<FSeam::GamesOfThroneDatabase::getGoodSeasons>(std::vector<int>({1,2,3,4,5,6}));
        fseamMock_Couchbase->dupeReturn<FSeam::GamesOfThroneDatabase::getNotSoGoodSeasons>(std::vector<int>({8}));

        REQUIRE_THROWS_WITH(testingClass.isGoodGamesOfThroneSeason(7), Catch::Contains("The season is not referenced"));

        // Because data are present in the cache, SQL connector is never called
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::GamesOfThroneDatabase::getGoodSeasons::NAME, FSeam::NeverCalled{}));
        REQUIRE(fseamMock_SqlDatabase->verify(FSeam::GamesOfThroneDatabase::getNotSoGoodSeasons::NAME, FSeam::NeverCalled{}));
    }

    FSeam::MockVerifier::cleanUp();
}
