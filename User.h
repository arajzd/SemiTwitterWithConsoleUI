#include <vector>
#include <string>
#include <iostream>
#include "utils.h"

#ifndef FINALPROJECT_USER_H
#define FINALPROJECT_USER_H

using namespace std;

class Tweet;

class User {
    string username;
    string displayName;
    vector<Tweet *> tweets;
public:

    User(const string &username, const string &displayName) : username(username), displayName(displayName) {}

    ~User() = default;

    void addTweet(Tweet *newTweet);

    vector<pair<string, string> > getPairOfTweetIdVsTweetsString();

    const string &getUsername() const { return username; }

    const string &getDisplayName() const { return displayName; }

    bool operator==(const User &rhs) const;

};


#endif //FINALPROJECT_USER_H
