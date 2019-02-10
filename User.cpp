#include "User.h"
#include "Tweet.h"

vector<pair<string, string> > User::getPairOfTweetIdVsTweetsString() {
    vector<pair<string, string> > listOfTweetsString;
    for (int i = 0; i < tweets.size(); ++i) {
        listOfTweetsString.push_back(make_pair(tweets[i]->getTweetIdVsSummaryStringPair().first,
                                               tweets[i]->getTweetIdVsSummaryStringPair().second));
    }
    return listOfTweetsString;
}

void User::addTweet(Tweet *newTweet) {
    tweets.push_back(newTweet);
}

bool User::operator==(const User &rhs) const {
    return username == rhs.username;
}

