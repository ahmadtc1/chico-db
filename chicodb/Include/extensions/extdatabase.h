#ifndef EXTDATABASE_H
#define EXTDATABASE_H
#include "database.h"

namespace chicodbext {


using namespace chicodb;

class EmbeddedDatabase : public IDatabase
{
public:
    EmbeddedDatabase(std::string dbName, std::string fullPath);
    ~EmbeddedDatabase();

    std::string getDirectory(void);

    // key-value use cases
    void setKeyValue(std::string key, std::string value);
    std::string getKeyValue(std::string key);

    // management functions
    const static std::unique_ptr<IDatabase> createEmpty(std::string dbName);
    const static std::unique_ptr<IDatabase> loadDB(std::string dbName);
    void destroy();

    class Impl;

private:
    std::unique_ptr<Impl> mImpl;
};

}
#endif // EXTDATABASE_H
