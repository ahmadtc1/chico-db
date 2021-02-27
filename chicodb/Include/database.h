#ifndef Database_H
#define Database_H

#include <string>

namespace chicodb {

// purely being used as an interface for EmbeddedDatabase
class IDatabase
{
public:
    IDatabase() = default;
    virtual ~IDatabase() = 0;
    virtual std::string getDirectory(void) = 0;

    virtual void setKeyValue(std::string key, std::string value) = 0;
    virtual std::string getKeyValue(std::string key) = 0;

    // management functions
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbName);
    static const std::unique_ptr<IDatabase> loadDB(std::string dbName);
    virtual void destroy() = 0;
};

}

#endif // Database_H
