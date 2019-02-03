
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
#include <iostream>

#ifndef FINALPROJECT_SOCIALNETWORK_H
#define FINALPROJECT_SOCIALNETWORK_H

using namespace std;

class SocialNetwork {
private:
    DataBase *dataBase;
    vector<User*> users;
    vector<Tweet *> tweets;
    User *currentUser;

public:
    SocialNetwork() {
        dataBase = new DataBase();
        currentUser = NULL;
    }

    virtual ~SocialNetwork();

    void signUp(string username, string displayName, string password);

    void login(string username, string password);

    void sendNotifToUsers(EventType eventType, Tweet *involvedTweet, vector<User *> toBeNotifiedUsers);

    void sendNotifToUsers(EventType eventType, string commentId, vector<User *> toBeNotifiedUsers);

    void tweet(string text, vector<string> newTagStrings, vector<string> mentionStrings);

    void showTweet(const string &tweetId);

    void showUserTweets(const string &username);

    void showComment(const string &commentId);

    void replyTheComment(const string &commentId, const string &replyText);

    void like(const string &tweetId);

    void dislike(string tweetId);

    void replyTheReply(string replyId, string replyText);

    void searchForTags(const string &tagText);

    void comment(const string &tweetId, const string &text);

    void showNotifications();

    void showReply(string replyId);

    void follow(const string &toBeFollowedUser);

    void unfollow(const string &toBeUnfollowedUser);

    void retweet(const string &tweetId);

    void logOut();

    int getIndexOfDesiredUser(const string &username);

    int getIndexByDisplayName(const string & displayName);

    int getIndexOfDesiredTweet(const string &tweetId);

    string determineTweetId();

    inline bool userIsLoggedIn() const;
};


#endif //FINALPROJECT_SOCIALNETWORK_H
