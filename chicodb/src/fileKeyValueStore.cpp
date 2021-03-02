#include "extensions/extdatabase.h"

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace chicodbext {

namespace fs = std::experimental::filesystem;

class FileKeyValueStore::Impl
{
public:
    Impl(std::string fullPath);
    std::string m_fullPath;

private:
};

FileKeyValueStore::Impl::Impl(std::string fullPath)
{
    m_fullPath = fullPath;
}

FileKeyValueStore::FileKeyValueStore(std::string fullPath)
    : mImpl(std::make_unique<FileKeyValueStore::Impl>(fullPath))
{
    if (!fs::exists(fullPath))
    {
        fs::create_directory(fullPath);
    }
}

FileKeyValueStore::~FileKeyValueStore()
{

}

// kv use cases
void FileKeyValueStore::setKeyValue(std::string key, std::string value)
{
    // Adding handling for names with slashes using a delimiter
    // If the key contains a slash we replace it with a delimeter character ("--" represents a slash)
    if (key.find("/") != std::string::npos)
    {
        // erase the slash from the key
        int slashIndex = key.find("/");
        key.erase(slashIndex, 1);
        key.insert(slashIndex, "--");
    }
    std::ofstream os;
    os.open(mImpl->m_fullPath + "/" + key + "_string.kv",
            std::ios::out | std::ios::trunc);
    os << value;
    os.close();
}

std::string FileKeyValueStore::getKeyValue(std::string key)
{
    if (key.find("/") != std::string::npos)
    {
        // erase the slash from the key
        int slashIndex = key.find("/");
        key.erase(slashIndex, 1);
        key.insert(slashIndex, "--");
    }

    std::ifstream t(mImpl->m_fullPath + "/" + key + "_string.kv");
    std::string value;
    t.seekg(0, std::ios::end);
      value.reserve(t.tellg());
      t.seekg(0, std::ios::beg);

      value.assign((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    return value;
}

void FileKeyValueStore::loadKeysInto(std::function<void (std::string, std::string)> callback)
{
    for (auto& p : fs::directory_iterator(mImpl->m_fullPath))
    {
        if (p.exits() && p.is_regular_file())
        {
            // check if the extension is .kv
            if (".kv" == p.path().extension())
            {
                std::string keyWithString = p.path().filename();

                std::string key = keyWithString.substr(0, keyWithString.length() - 10); // dangerous bc we're assuming all files end with "_string.kv" 
                std::ifstream t(p.path());
                std::string value;

                t.seekg(0, std::ios::end);
                value.reserve(t.tellg());
                t.seekg(0, std::ios::beg);

                value.assign(std::ifstreambuf_iterator<char>(t),
                             std::ifstreambuf_iterator<char>());

                callback(key, value);
            }
        }
    }
}

void FileKeyValueStore::clear()
{
    if (fs::exists(mImpl->m_fullPath))
    {
        fs::remove_all(mImpl->m_fullPath);
    }
}

}
