
#ifndef FINALPROJECT_RETWEET_H
#define FINALPROJECT_RETWEET_H


#include "Tweet.h"

class Retweet : public Tweet {

public:
    Retweet(const string &_tweetId, Tweet _newRetweet, User *_involvedUser) : Tweet(_newRetweet) {
        involvedUser = _involvedUser;
        tweetId = _tweetId;
        numberOfRetweets = 0;
        likers.clear();
    }

    string getTweetContentString() override;

    pair<string, string> getTweetIdVsSummaryStringPair() override;

    vector<User *> getMentrionedUsers() { return mentionedUsers; }
};


#endif //FINALPROJECT_RETWEET_H
