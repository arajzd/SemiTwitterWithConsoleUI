
#ifndef FINALPROJECT_RETWEET_H
#define FINALPROJECT_RETWEET_H


#include "Tweet.h"

class Retweet : public Tweet {

public:
    Retweet(const string &tweetId, const Tweet &newRetweet, User *_involvedUser) : Tweet(newRetweet) {
        involvedUser = _involvedUser;
        TweetId = tweetId;
        numberOfRetweets = 0;
        likers.clear();
    }
    void printTweet();

    void printBriefly();

    vector<User*> getMentrionedUsers(){ return mentionedUsers;}
};


#endif //FINALPROJECT_RETWEET_H
