

#include "DataBase.h"

string DataBase::getMatchedUserProfile(string username, string password) {
    for (int i = 0; i < data.size(); ++i) {
        if (data[i].first == username && data[i].second == password) {
            return username;
        }
    }
    throw InvalidUserNameAndPassword();
}

void DataBase::signUp(string username, string password) {
    for (int i = 0; i < data.size(); ++i) {
        if (data[i].first == username) {
            throw UsernameAlreadyExists();
        }
    }
    pair<string, string> newUser(username, password);
    data.push_back(newUser);
}
