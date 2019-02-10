
#include "utils.h"
#include <vector>
#include <string>
#include "utility"

#ifndef FINALPROJECT_DATABASE_H
#define FINALPROJECT_DATABASE_H
using namespace std;

class DataBase {
    vector<pair<string, string> > data;
public:
    DataBase() = default;

public:
    void signUp(string username, string password);

    string getMatchedUserProfile(string username, string password);
};


#endif //FINALPROJECT_DATABASE_H
