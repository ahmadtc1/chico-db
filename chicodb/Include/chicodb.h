#ifndef CHICODB_H
#define CHICODB_H

// WARNING : this should ONLY include Client API files
// eg. nothing with extensions!

#include <string>
#include "database.h"

namespace chicodb {



class ChicoDB
{
public:
    ChicoDB();


    static std::unique_ptr<IDatabase> createEmptyDB(std::string& dbName);
    static std::unique_ptr<IDatabase> loadDB(std::string& dbName);
};

}
#endif // CHICODB_H
