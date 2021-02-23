#include "chicodb.h"

ChicoDB::ChicoDB()
{
}

Database ChicoDB::createEmptyDB(std::string &dbName)
{
    return Database::createEmpty(dbName);
}
