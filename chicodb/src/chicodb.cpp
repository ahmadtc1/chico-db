#include "chicodb.h"
#include "extensions/extdatabase.h"

using namespace chicodb;
using namespace chicodbext;

ChicoDB::ChicoDB()
{
}

std::unique_ptr<IDatabase> ChicoDB::createEmptyDB(std::string &dbName)
{
    return EmbeddedDatabase::createEmpty(dbName);
}

std::unique_ptr<IDatabase> ChicoDB::createEmptyDB(std::string &dbName, std::unique_ptr<KeyValueStore> &kvStore)
{
    return EmbeddedDatabase::createEmpty(dbName, kvStore);
}

std::unique_ptr<IDatabase> ChicoDB::loadDB(std::string &dbName)
{
    return EmbeddedDatabase::loadDB(dbName);
}
