#ifndef Database_H
#define Database_H

#include <string>

class Database
{
public:
    Database(std::string dbName, std::string fullPath);

    std::string getDirectory(void);

    void setKeyValue(std::string key, std::string value);
    std::string getKeyValue(std::string key);

    // management functions
    static Database createEmpty(std::string dbName);
    void destroy();

protected:
    std::string m_name;
    std::string m_fullPath;
    //TODO std::pointer<DataBaseImpl> pImpl;
};

#endif // Database_H
