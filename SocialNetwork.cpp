
#include "SocialNetwork.h"
#include "Retweet.h"

void SocialNetwork::signUp(string username, string displayName, string password) {
    if (username.empty() || displayName.empty() || password.empty()) {
        throw InvalidInputException();
    }
    dataBase->signUp(username, password);
    User *newUser = new User(username, displayName);
    users.push_back(newUser);
    /// here is the code for adding tweets;
    addSomePreparedTweet(username, password);
}

void SocialNetwork::addSomePreparedTweet(const string &username, const string &password) {
    login(username, password);
    for (int i = 0; i < 3; ++i) {
        tweet("hello" + to_string(i), vector<string>(1, (to_string(i) + "thTweet")), vector<string>(1, "a"));
    }
    logOut();
}

void SocialNetwork::login(string username, string password) {
    if (username.empty() || password.empty()) {
        throw InvalidInputException();
    }
    string toBeLoggedInUser = dataBase->getMatchedUserProfile(username, password);
    int userIndex = getIndexOfDesiredUser(toBeLoggedInUser);
    if (userIndex != INVALID_INDEX) {
        currentUser = users[userIndex];
    } else {
        throw InvalidInputException();
    }
}

void SocialNetwork::logOut() {
    currentUser = nullptr;
}

string SocialNetwork::determineTweetId() {
    int tweetId = tweets.size();
    string tweetIdString;
    ostringstream convert;
    convert << tweetId;
    tweetIdString = convert.str();
    return tweetIdString;
}

void SocialNetwork::tweet(string text, vector<string> newTagStrings, vector<string> mentionStrings) {
    if (userIsLoggedIn()) {
        string tweetId = determineTweetId();
        vector<User *> mentionedUsersAddress;
        Tweet *newTweet = new Tweet(tweetId, text, currentUser);
        for (int i = 0; i < newTagStrings.size(); ++i) {
            Tag *newTag = new Tag(newTagStrings[i]);
            newTweet->addTag(newTag);
        }
        for (int j = 0; j < mentionStrings.size(); ++j) {
            int userIndex = getIndexOfDesiredUser(mentionStrings[j]);
            if (userIndex != INVALID_INDEX) {
                mentionedUsersAddress.push_back(users[userIndex]);
                newTweet->addMention(users[userIndex]);
            }
        }
        tweets.push_back(newTweet);
        currentUser->addTweet(newTweet);
    } else {
        throw UserNotLoggedIn();
    }

}


string SocialNetwork::showTweet(const string &tweetId) {
    int tweetIndex = getIndexOfDesiredTweet(tweetId);
    string tweetString;
    if (tweetIndex != INVALID_INDEX) {
        tweetString = tweets[tweetIndex]->getTweetContentString();
    }
    return tweetString;
}

int SocialNetwork::getIndexOfDesiredUser(const string &username) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username) {
            return i;
        }
    }
    return INVALID_INDEX;
}

int SocialNetwork::getIndexOfDesiredTweet(const string &tweetId) {
    for (int i = 0; i < tweets.size(); ++i) {
        if (tweets[i]->getTweetId() == tweetId) {
            return i;
        }
    }
    return INVALID_INDEX;
}

vector<pair<string, string> > SocialNetwork::showUserTweets(const string &username) {
    vector<pair<string, string> > userTweets;
    int userIndex = getIndexOfDesiredUser(username);
    if (userIndex != INVALID_INDEX) {
        if (!(users[userIndex]->getPairOfTweetIdVsTweetsString().empty())) {
            userTweets = users[userIndex]->getPairOfTweetIdVsTweetsString();
            //todo think ?!?
        }
    }
    return userTweets;
}

vector<pair<string, string> > SocialNetwork::searchForTags(string tagText) {
    vector<pair<string, string> > tweetsWithThisTag;
    for (int i = 0; i < tweets.size(); ++i) {
        if (tweets[i]->hasThisTag(tagText)) {
            tweetsWithThisTag.push_back(make_pair(tweets[i]->getTweetIdVsSummaryStringPair().first,
                                                  tweets[i]->getTweetIdVsSummaryStringPair().second + LINE_BREAK));
        }
    }
    return tweetsWithThisTag;
}

void SocialNetwork::like(string tweetId) {
    if (userIsLoggedIn()) {
        int tweetIndex = getIndexOfDesiredTweet(tweetId);
        tweets[tweetIndex]->like(currentUser->getUsername());
    } else {
        throw UserNotLoggedIn();
    }
}

bool SocialNetwork::userIsLoggedIn() const { return currentUser != nullptr; }

void SocialNetwork::dislike(string tweetId) {
    if (userIsLoggedIn()) {
        int tweetIndex = getIndexOfDesiredTweet(tweetId);
        tweets[tweetIndex]->dislike(currentUser->getUsername());
    }
}

void SocialNetwork::retweet(string tweetId) {
    if (userIsLoggedIn()) {
        string retweetId = determineTweetId();
        int tweetIndex = getIndexOfDesiredTweet(tweetId);
        tweets[tweetIndex]->addRetweet();
        auto newRetweet = new Retweet(retweetId, *tweets[tweetIndex], currentUser);
        tweets.push_back(newRetweet);
        currentUser->addTweet(newRetweet);
    } else {
        throw UserNotLoggedIn();
    }
}

string SocialNetwork::getCurrentUserDisplayName() const {
    return currentUser->getDisplayName();
}

void SocialNetwork::login(const string &toBeLoggedInUser) {
    int userIndex = getIndexOfDesiredUser(toBeLoggedInUser);
    if (userIndex != INVALID_INDEX) {
        currentUser = users[userIndex];
    }
}
/*
SocialNetwork::~SocialNetwork() {
    for (auto &user : users) {
        delete user;
    }
    for (auto &tweet : tweets) {
        delete tweet;
    }

}
*/