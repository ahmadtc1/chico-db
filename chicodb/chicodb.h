#ifndef CHICODB_H
#define CHICODB_H

#include <string>
#include "Database.h"

class ChicoDB
{
public:
    ChicoDB();


    static Database createEmptyDB(std::string& dbName);
};

#endif // CHICODB_H
