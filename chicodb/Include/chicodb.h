#ifndef CHICODB_H
#define CHICODB_H

#include <string>
#include "database.h"

namespace chicodb {



class ChicoDB
{
public:
    ChicoDB();


    static Database createEmptyDB(std::string& dbName);
    static Database loadDB(std::string& dbName);
};

}
#endif // CHICODB_H
