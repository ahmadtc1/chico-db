#include "database.h"
#include "extensions/extdatabase.h"
#include <experimental/filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::experimental::filesystem;

using namespace chicodb;
using namespace chicodbext;

// 'Hidden' DB Impl class
class EmbeddedDatabase::Impl : public IDatabase
{
public:
    Impl(std::string dbName, std::string fullPath);
    ~Impl();

    std::string getDirectory(void);

    // key-value methods
    void setKeyValue(std::string key, std::string value);
    std::string getKeyValue(std::string key);

    // management functions
    const static std::unique_ptr<IDatabase> createEmpty(std::string dbName);
    const static std::unique_ptr<IDatabase> loadDB(std::string dbName);
    void destroy();

private:
    std::string m_name;
    std::string m_fullPath;
};

EmbeddedDatabase::Impl::Impl(std::string dbName, std::string fullPath)
{
    m_name = dbName;
    m_fullPath = fullPath;
}

EmbeddedDatabase::Impl::~Impl()
{

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
    if (!fs.exists(dbFolder))
    {
        fs::cerate_directory(dbFolder);
    }

    return std::make_unique<EmbeddedDatabase::Impl>(dbName, dbFolder);
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::loadDB(std::string dbName)
{
    std::string baseDir = ".chicodb";
    std::string dbFolder = baseDir + "/" + dbName;
    return std::make_unique<EmbeddedDatabase::Impl>(EmbeddedDatabase::Impl(dbName, dbFolder));
}

void EmbeddedDatabase::Impl::destroy()
{
    if (fs::exists(m_fullPath))
    {
        fs::remove_all(m_fullPath);
    }
}


// Instance user functions
std::string EmbeddedDatabase::Impl::getDirectory()
{
    return m_fullPath;
}

std::string EmbeddedDatabase::Impl::getKeyValue(std::string key)
{
    std::ifstream ifs(m_fullPath + "/" + key + "_string.kv");
    std::string value;

    ifs.seekg(0, std::ios::end);
    value.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    value.assign((std::ifstreambuf_iterator<char>(t)),
                 std::ifstreambuf_iterator<char>());

    return value;
}

void EmbeddedDatabase::Impl::setKeyValue(std::string key, std::string value)
{
    std::ofstream os;
    os.open(m_fullPath + "/" + key + "_string.kv:", std::ios::out | std::ios::trunc);
    os << value;
    os.close();
}


// Embedded Database

EmbeddedDatabase::EmbeddedDatabase(std::string dbName, std::string fullPath)
    : mImpl(std::make_unique<EmbeddedDatabase::Impl>(dbName, fullPath))
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

