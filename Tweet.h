
#include <string>
#include <vector>
#include "User.h"
#include "utils.h"
#include <iostream>

#ifndef FINALPROJECT_TWEET_H
#define FINALPROJECT_TWEET_H

using namespace std;

class Retweet;

class Tag;

class Tweet {
protected:
    string tweetId;
    string text;
    User *involvedUser;
    vector<Tag *> tags;
    vector<User *> mentionedUsers;
    vector<string> likers;
    int numberOfRetweets;

public:

    Tweet(const string &TweetId, const string &text, User *involvedUser);

    const string &getTweetId() const { return tweetId; }

    virtual string getTweetContentString();

    virtual pair<string, string> getTweetIdVsSummaryStringPair();

    void addTag(Tag *newTag);

    void addMention(User *newMention);

    void like(string likerUsername);

    void dislike(string dislikerUsername);

    User *getInvolvedUser();

    bool hasThisTag(string tagText);

    void addRetweet();

};


#endif //FINALPROJECT_TWEET_H
