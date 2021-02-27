#include <iostream>
#include "cxxopts.hpp"
#include "chicodb/chicodb.h"

using namespace chicodb;

cxxopts::Options options("chicodb-cli", "CLI for ChicoDB");

void printUsage()
{
    std::cout << "Whoops, bad config!" << std::endl;
}


// Using github/jarro2783 as a header library for command line arguments
int main(int argc, char* argv[])
{
    options.add_options()
        ("c, create", "Create a DB")
        ("d, destroy", "Destroy a DB")
        ("s, set", "Set a key in a DB")
        ("g, get", "Get a key from a DB")
        ("n, name", "Database name (required)")
        ("k, key", "Key to set/get", cxxopts::value<std::string>())
        ("value", "Value to set", cxxopts::value<std::string>())
    ;
    auto result = options.parse(argc, argv);

    if (result.count("c") == 1)
    {
        if (result.count("n") == 0)
        {
            std::cout << "You must specify a database name with -n <name>" << std::endl;
            printUsage();
            return 1;
        }

        // create the database
        std::string dbName = result["n"].as<std::string>();
        std::unique_ptr<chicodb::IDatabase> db(ChicoDB::createEmptyDB(dbName));
        return 0;
    }

    if (result.count("d") == 1)
    {
        if (result.count("n") == 0)
        {
            std::cout << "You must specify a database name with -n <name>" << std::endl;
            printUsage();
            return 1;
        }

        // destroy the database
        std::string dbName = result["n"].as<std::string>();
        std::unique_ptr<chicodb::IDatabase> db(ChicoDB::loadDB(dbName));
        db -> destroy();
        return 0;
    }

    if (result.count("s") == 1)
    {
        if (result.count("n") == 0)
        {
            std::cout << "You must specify a database name with -n <name>" << std::endl;
            printUsage();
            return 1;
        }

        if (result.count("k") == 0)
        {
            std::cout << "You must specify a key to set with -k <name>" << std::endl;
            printUsage();
            return 1;
        }


        if (result.count("v") == 0)
        {
            std::cout << "You must specify a value to set with -v <value>" << std::endl;
            printUsage();
            return 1;
        }

        std::string dbName = result["n"].as<std::string>();
        std::string key = result["k"].as<std::string>();
        std::string value = result["v"].as<std::string>();
        std::unique_ptr<chicodb::IDatabase> db(ChicoDB::loadDB(dbName));
        db -> setKeyValue(key, value);
        return 0;
    }

    if (result.count("g") == 1)
    {
        if (result.count("n") == 0)
        {
            std::cout << "You must specify a database name with -n <name>" << std::endl;
            printUsage();
            return 1;
        }

        if (result.count("k") == 0)
        {
            std::cout << "You must specify a key to set with -k <name>" << std::endl;
            printUsage();
            return 1;
        }


        std::string dbName = result["n"].as<std::string>();
        std::string key = result["k"].as<std::string>();
        std::unique_ptr<chicodb::IDatabase> db(ChicoDB::loadDB(dbName));
        std::cout << db -> getKeyValue(key);
        return 0;
    }

    std::cout << "No command specified" << std::endl;
    printUsage();
    return 1;
}
