#include "utils.h"
#include <memory>
#include <string>
#include "utils.h"
#include <string>
#include <vector>
#include "User.h"
#include "DataBase.h"
#include "Tag.h"
#include "Tweet.h"
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <memory>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <functional>
#include <map>

#define INVALID_SESSION_ID "";

#ifndef FINALPROJECT_INTERFACE_H
#define FINALPROJECT_INTERFACE_H

class SocialNetwork;

class Interface {
private:
    unique_ptr<SocialNetwork> socialNetwork;
    map<string, string> sessionIdVsUsername;

private:
    void login(const string &username);

public:

    Interface();

   // ~Interface() = default;

    string showHomeHTML(const string &sessionId, HomePageType homePageType = DEFAULT, const string &searchString = "");

    void signUp(const string &username, const string &displayName, const string &password);

    void login(const string &username, const string &password, const string &sessionId);

    void tweet(string tweetString);

    void retweet(const string &toBeRetweetedId, const string &sessionId);

    string showJeekDetails(const string &sessionId, const string &tweetId);

    void like(const string &tweetId, const string &sessionId);

    void dislike(const string &tweetId, const string &sessionId);

    string getHomeDefaultPage();

    void logOut();

    static vector<string> parseInput(const string &inputString);

    bool isSessionIdValid(const string &sessionId) { return sessionId != INVALID_SESSION_ID; }

};


#endif //FINALPROJECT_INTERFACE_H
