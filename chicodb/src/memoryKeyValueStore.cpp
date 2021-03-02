#include "extensions/extdatabase.h"
#include <unordered_map>

namespace chicodbext {

class MemoryKeyValueStore::Impl {
public:
    Impl();
    Impl(std::unique_ptr<KeyValueStore>& toCache);

    std::unordered_map<std::string, std::string> m_keyValueStore;
    std::optional<std::unique_ptr<KeyValueStore>> m_cachedStore;

private:

};

MemoryKeyValueStore::Impl::Impl(): m_keyValueStore(), m_cachedStore()
{
}

MemoryKeyValueStore::Impl::Impl(std::unique_ptr<KeyValueStore>& toCache)
    : m_keyValueStore(), m_cachedStore(toCache.release())
{
}

MemoryKeyValueStore::MemoryKeyValueStore()
    : mImpl(std::make_unique<MemoryKeyValueStore::Impl>())
{
}

MemoryKeyValueStore::MemoryKeyValueStore(std::unique_ptr<KeyValueStore>& toCache)
    :mImpl(std::make_unique<MemoryKeyValueStore::Impl>(toCache))
{
    mImpl->m_cachedStore->get()->loadKeysInto([this](std::string key, std::string value){
        mImpl->m_keyValueStore.insert({key, value});
    });
}

MemoryKeyValueStore::~MemoryKeyValueStore()
{
}

// kv use cases
void MemoryKeyValueStore::setKeyValue(std::string key, std::string value)
{
    if (key.find("/") != std::string::npos)
    {
        // erase the slash from the key
        int slashIndex = key.find("/");
        key.erase(slashIndex, 1);
        key.insert(slashIndex, "--");
    }

    mImpl->m_keyValueStore.insert({key, value});
    if (mImpl->m_cachedStore)
    {
        mImpl->m_cachedStore->get()->setKeyValue(key, value);
    }
}

std::string MemoryKeyValueStore::getKeyValue(std::string key)
{
    if (key.find("/") != std::string::npos)
    {
        // erase the slash from the key
        int slashIndex = key.find("/");
        key.erase(slashIndex, 1);
        key.insert(slashIndex, "--");
    }

    const auto& v = mImpl->m_keyValueStore.find(key);
    if (v == mImpl->m_keyValueStore.end())
    {
        return ""; // dangerous - should add error handling
    }
    return v -> second;
}

void MemoryKeyValueStore::loadKeysInto(std::function<void (std::string, std::string)> callback)
{
    for (auto element : mImpl->m_keyValueStore)
    {
        callback(element.first, element.second);
    }
}

void MemoryKeyValueStore::clear()
{
    mImpl->m_keyValueStore.clear();
    if (mImpl->m_cachedStore)
    {
        mImpl->m_cachedStore->get()->clear();
    }
}

}

