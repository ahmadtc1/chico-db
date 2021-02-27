#include "tests.h"

//#include <experimental/filesystem>
#include <string>
#include "chicodb/chicodb.h"

//namespace fs = std::experimental::filesystem;

TEST_CASE("Create a new, empty Database", "[createEmptyDB]")
{
    /*
     * [Who] as a DB Admin
     * [What] create a new empty Database
     * [Value] to store and retrieve data
    */
    SECTION("Default settings")
    {
        std::string dbName = "myEmptyDB";
        std::unique_ptr<chicodb::IDatabase> db(chicodb::ChicoDB::createEmptyDB(dbName));

        /*
         *  We're successful when we:
         *  1 - return a valid Database reference
         *  2 - The DB has a folder existing on the filesystem
        */

        //REQUIRE((fs::is_directory(fs::status(db.getDirectory()))));

        //const auto& p = fs::directory_iterator(db.getDirectory()); // ensure Database is empty
        //REQUIRE((p == end(p)));

        db -> destroy();

        //REQUIRE(!fs.exists(fs.status(db.getDirectory())));
    }
}

TEST_CASE("Load an existing database", "[loadDB]")
{
    SECTION("Default Settings")
    {
        std::string dbName = "chicoDB";
        std::unique_ptr<chicodb::IDatabase> db(chicodb:ChicoDB::createEmptyDB(dbName));

        std::unique_ptr<chicodb::IDatabase> db2(chicodb::ChicoDB::loadDB(dbName));

        //REQUIRE(fs::is_directory(fs::status(db2 -> getDirectory())));

        //const auto& p = fs::directory_iterator(db2 -> getDirectory());
        //REQUIRE(p == end(p));

        db2 -> destroy();
        //REQUIRE(!fs::exists(fs::status(db2 -> getDirectory*(()))));
    }
}
