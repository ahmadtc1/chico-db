#include "database.h"
#include "extensions/extdatabase.h"
#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <unordered_map>

namespace fs = std::experimental::filesystem;

using namespace chicodb;
using namespace chicodbext;


/*

// Hidden store Impl class
class Store::Impl
{
public:
    Impl();
private:
};

Store::Impl::Impl()
{
}

// Hidden key value store Impl class
class KeyValueStore::Impl
{
public:
    Impl();

private:
};

KeyValueStore::Impl::Impl()
{
}

*/


// 'Hidden' DB Impl class
class EmbeddedDatabase::Impl : public IDatabase
{
public:
    Impl(std::string dbName, std::string fullPath);
    Impl(std::string dbName, std::string fullPath, std::unique_ptr<KeyValueStore>& kvStore);
    ~Impl();

    std::string getDirectory(void);

    // key-value methods
    void setKeyValue(std::string key, std::string value);
    std::string getKeyValue(std::string key);

    // management functions
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbName);
    static const std::unique_ptr<IDatabase> createEmpty(std::string dbName, std::unique_ptr<KeyValueStore>& kvStore);
    static const std::unique_ptr<IDatabase> loadDB(std::string dbName);
    void destroy();

private:
    std::string m_name;
    std::string m_fullPath;
    std::unique_ptr<KeyValueStore> m_keyValueStore;
};

EmbeddedDatabase::Impl::Impl(std::string dbName, std::string fullPath)
{
    m_name = dbName;
    m_fullPath = fullPath;

    std::unique_ptr<KeyValueStore> fileStore = std::make_unique<FileKeyValueStore>(fullPath);
    std::unique_ptr<KeyValueStore> memoryStore = std::make_unique<MemoryKeyValueStore>(fileStore);
    m_keyValueStore = std::move(memoryStore);
    // load all keys from disc to our map here
    // load any files with .kv in them
}

EmbeddedDatabase::Impl::Impl(std::string dbName, std::string fullPath, std::unique_ptr<KeyValueStore>& kvStore) : m_name(dbName), m_fullPath(fullPath), m_keyValueStore(kvStore.release())
{
}

EmbeddedDatabase::Impl::~Impl()
{
    // [Optional] flush the latest known state to disk
}

// Management Functions
const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::createEmpty(std::string dbName)
{
    std::string baseDir = ".chicodb";
    if (!fs.exists(baseDir))
    {
        fs::create_directory(baseDir);
    }

    std::string dbFolder = baseDir + "/" + dbName;
    return std::make_unique<EmbeddedDatabase::Impl>(dbName, dbFolder);
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::createEmpty(std::string dbName, std::unique_ptr<KeyValueStore>& kvStore)
{
    std::string baseDir = ".chicodb";
    if (!fs::exists(baseDir))
    {
        fs::create_directory(baseDir);
    }

    std::string dbFolder = baseDir + "/" + dbName;
    return std::make_unique<EmbeddedDatabase::Impl>(dbName, dbFolder, kvStore);
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::loadDB(std::string dbName)
{
    std::string baseDir = ".chicodb";
    std::string dbFolder = baseDir + "/" + dbName;
    return std::make_unique<EmbeddedDatabase::Impl>(EmbeddedDatabase::Impl(dbName, dbFolder));
}

void EmbeddedDatabase::Impl::destroy()
{
    m_keyValueStore -> clear();
}


// Instance user functions
std::string EmbeddedDatabase::Impl::getDirectory()
{
    return m_fullPath;
}

void EmbeddedDatabase::Impl::setKeyValue(std::string key, std::string value)
{
    m_keyValueStore->setKeyValue(key, value);
}

std::string EmbeddedDatabase::Impl::getKeyValue(std::string key)
{
    m_keyValueStore->getKeyValue(key);
}

// Embedded Database

EmbeddedDatabase::EmbeddedDatabase(std::string dbName, std::string fullPath)
    : mImpl(std::make_unique<EmbeddedDatabase::Impl>(dbName, fullPath))
{
}

EmbeddedDatabase::EmbeddedDatabase(std::string dbName, std::string fullPath, std::unique_ptr<KeyValueStore>& kvStore)
    : mImpl(std::make_unique<EmbeddedDatabase::Impl>(dbName, fullPath, kvStore))
{
}

EmbeddedDatabase::~EmbeddedDatabase()
{

}

// Management Functions
const std::unique_ptr<IDatabase>  EmbeddedDatabase::createEmpty(std::string dbName)
{
    EmbeddedDatabase::Impl::createEmpty(dbName);
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::createEmpty(std::string dbName, std::unique_ptr<KeyValueStore>& kvStore)
{
    return EmbeddedDatabase::Impl::createEmpty(dbName, kvStore);
}


const std::unique_ptr<IDatabase> EmbeddedDatabase::loadDB(std::string dbName)
{
    EmbeddedDatabase::Impl::loadDB((dbName));
}


void EmbeddedDatabase::destroy()
{
    mImpl -> destroy();
}


// Instance user functions
std::string EmbeddedDatabase::getDirectory()
{
    return mImpl -> getDirectory();
}

std::string EmbeddedDatabase::getKeyValue(std::string key)
{
    return mImpl -> getKeyValue(key);
}

void EmbeddedDatabase::setKeyValue(std::string key, std::string value)
{
    mImpl -> setKeyValue(key, value);
}


// High level DB Client API Implementation

