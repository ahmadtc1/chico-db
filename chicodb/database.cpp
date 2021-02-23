#include "database.h"
#include <experimental/filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::experimental::filesystem;

Database::Database(std::string dbName, std::string fullPath)
{
    m_name = dbName;
    m_fullPath = fullPath;
}

// Management Functions
std::string Database::getDirectory()
{
    return m_fullPath;
}

void Database::destroy()
{
    if (fs::exists(m_fullPath))
    {
        fs::remove_all(m_fullPath);
    }
}




Database Database::createEmpty(std::string dbName)
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

    return Database(dbName, dbFolder);
}


std::string Database::getKeyValue(std::string key)
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

void Database::setKeyValue(std::string key, std::string value)
{
    std::ofstream os;
    os.open(m_fullPath + "/" + key + "_string.kv:", std::ios::out | std::ios::trunc);
    os << value;
    os.close();
}


