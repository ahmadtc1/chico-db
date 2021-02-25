#include "chicodb.h"

using namespace chicodb;

ChicoDB::ChicoDB()
{
}

Database ChicoDB::createEmptyDB(std::string &dbName)
{
    return Database::createEmpty(dbName);
}

Database ChicoDB::loadDB(std::string &dbName)
{
    return Database::loadDB(dbName);
}
