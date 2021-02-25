#include "catch.hpp"
#include "chicodb.h"
#include "chicodb/chicodb.h"\

TEST_CASE("Store and retrieve a value", "[setKeyValue, getKeyValue]")
{

    SECTION("Basic get and store")
    {
        std::string dbName = "chicosdb";
        chicodb::Database db(chicodb::ChicoDB::createEmptyDB(dbName));


        std::string key = "cockatiel";
        std::string value = "birb";
        db.setKeyValue(key, value);
        REQUIRE(value == db.getKeyValue(key));

        db.destroy();
    }
}
