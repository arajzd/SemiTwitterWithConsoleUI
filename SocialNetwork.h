#include "Interface.h"
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

#ifndef FINALPROJECT_SOCIALNETWORK_H
#define FINALPROJECT_SOCIALNETWORK_H


using namespace std;

class SocialNetwork {
private:
    unique_ptr<DataBase> dataBase;
    vector<User *> users;
    vector<Tweet *> tweets;
    User *currentUser;

public:
    SocialNetwork() {
        unique_ptr<DataBase> _dataBase(new DataBase());
        dataBase = move(_dataBase);
        currentUser = nullptr;
    }

    //~SocialNetwork();

    void signUp(string username, string displayName, string password);

    void login(string username, string password);

    void tweet(string text, vector<string> newTagStrings, vector<string> mentionStrings);

    string showTweet(const string &tweetId);

    vector<pair<string, string> > showUserTweets(const string &username);

    void like(string tweetId);

    void dislike(string tweetId);

    vector<pair<string, string> > searchForTags(string tagText);

    void retweet(string tweetId);

    string getCurrentUserDisplayName() const;

    void logOut();

    int getIndexOfDesiredUser(const string &username);

    int getIndexOfDesiredTweet(const string &tweetId);

    string determineTweetId();

    inline bool userIsLoggedIn() const;

    void addSomePreparedTweet(const string &username, const string &password);

    void login(const string &toBeLoggedInUser);

};


#endif //FINALPROJECT_SOCIALNETWORK_H
