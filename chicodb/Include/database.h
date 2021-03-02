#ifndef Database_H
#define Database_H

#include <string>

namespace chicodb {

class Store {
public:
    Store() = default;
    virtual ~Store() = default;
};

class KeyValueStore : public Store{
public:
    KeyValueStore() = default;
    virtual ~KeyValueStore() = default;

    // kv end user functions
    virtual void setKeyValue(std::string key, std::string value) = 0;
    virtual std::string getKeyValue(std::string value) = 0;

    // kv management funcs
    virtual void loadKeysInto(std::function<void(std::string key, std::string value)> callback) = 0;
    virtual void clear() = 0;
};

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
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbName, std::unique_ptr<KeyValueStore>& kvStore);
    static const std::unique_ptr<IDatabase> loadDB(std::string dbName);
    virtual void destroy() = 0;
};

}

#endif // Database_H
