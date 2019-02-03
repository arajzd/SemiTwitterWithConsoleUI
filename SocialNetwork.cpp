
#include "SocialNetwork.h"
#include "Retweet.h"

void SocialNetwork::signUp(string username, string displayName, string password) {
    dataBase->signUp(username, password);
    User *newUser = new User(username, displayName);
    users.push_back(newUser);
}

void SocialNetwork::login(string username, string password) {
    string toBeLoggedInUser = dataBase->getMatchedUserProfile(username, password);
    int userIndex = getIndexOfDesiredUser(toBeLoggedInUser);
    if (userIndex != INVALID_INDEX) {
        currentUser = users[userIndex];
    } else {
        throw InvalidInputException();
    }
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
        sendNotifToUsers(MENTION, newTweet, mentionedUsersAddress);
        sendNotifToUsers(TWEET, newTweet, currentUser->getFollowers());
    } else {
        throw UserNotLoggedIn();
    }

}

void SocialNetwork::logOut() {
    if (userIsLoggedIn()) {
        currentUser = NULL;
    } else {
        throw UserNotLoggedIn();
    }

}

void SocialNetwork::sendNotifToUsers(EventType eventType, Tweet *involvedTweet, vector<User *> toBeNotifiedUsers) {
    for (int i = 0; i < toBeNotifiedUsers.size(); ++i) {
        toBeNotifiedUsers[i]->addEvent(eventType, currentUser, involvedTweet);
    }
}

void SocialNetwork::showTweet(const string &tweetId) {
    int tweetIndex = getIndexOfDesiredTweet(tweetId);
    if (tweetIndex != INVALID_INDEX) {
        tweets[tweetIndex]->printTweet();
    }
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

void SocialNetwork::showUserTweets(const string &username) {
    int userIndex = getIndexOfDesiredUser(username);
    users[userIndex]->printListOfTweets();
}

void SocialNetwork::searchForTags(const string &tagText) {
    for (int i = 0; i < tweets.size(); ++i) {
        if (tweets[i]->hasThisTag(tagText)) {
            tweets[i]->printBriefly();
            cout << endl;
        }
    }

}

void SocialNetwork::comment(const string &tweetId, const string &text) {
    if (userIsLoggedIn()) {
        int tweetIndex = getIndexOfDesiredTweet(tweetId);
        vector<User *> mentionedUsers;
        mentionedUsers.push_back(tweets[tweetIndex]->getInvolvedUser());
        tweets[tweetIndex]->addComment(text, currentUser->getDisplayName());
        sendNotifToUsers(COMMENT, tweets[tweetIndex], mentionedUsers);
    } else {
        throw UserNotLoggedIn();
    }
}

void SocialNetwork::showComment(const string &commentId) {
    for (int i = 0; i < tweets.size(); ++i) {
        if (tweets[i]->hasThisComment(commentId)) {
            tweets[i]->printThisComment(commentId);
        }
    }
}

void SocialNetwork::replyTheComment(const string &commentId, const string &replyText) {
    if (userIsLoggedIn()) {
        for (int i = 0; i < tweets.size(); ++i) {
            if (tweets[i]->hasThisComment(commentId)) {
                tweets[i]->addThisReply(replyText, commentId, currentUser->getDisplayName());
                string commenterDisplayName = tweets[i]->getThisCommentsUser(commentId);
                int indexOfCommenter = getIndexByDisplayName(commenterDisplayName);
                vector<User *> toBeNotifiedUser(1, users[indexOfCommenter]);
                sendNotifToUsers(REPLY, commentId, toBeNotifiedUser);
            }
        }
    } else {
        throw UserNotLoggedIn();
    }
}

void SocialNetwork::showReply(string replyId) {
    for (int i = 0; i < tweets.size(); ++i) {
        tweets[i]->printThisReply(replyId);
    }
}

void SocialNetwork::replyTheReply(string replyId, string replyText) {
    if (userIsLoggedIn()) {
        for (int i = 0; i < tweets.size(); ++i) {
            if (tweets[i]->CommentsHaveThisReply(replyId)) {
                tweets[i]->addThisReplyToReply(replyText, replyId, currentUser->getDisplayName());
            }
        }
    } else {
        throw UserNotLoggedIn();
    }
}

void SocialNetwork::like(const string &tweetId) {
    if (userIsLoggedIn()) {
        int tweetIndex = getIndexOfDesiredTweet(tweetId);
        tweets[tweetIndex]->like(currentUser->getUsername());
        vector<User *> toBeNotifiedUsers(1, tweets[tweetIndex]->getInvolvedUser());
        sendNotifToUsers(LIKE, tweets[tweetIndex], toBeNotifiedUsers);
    } else {
        throw UserNotLoggedIn();
    }
}

bool SocialNetwork::userIsLoggedIn() const { return currentUser != NULL; }

void SocialNetwork::dislike(string tweetId) {
    if (userIsLoggedIn()) {
        int tweetIndex = getIndexOfDesiredTweet(tweetId);
        tweets[tweetIndex]->dislike(currentUser->getUsername());
        vector<User *> toBeNotifiedUsers(1, tweets[tweetIndex]->getInvolvedUser());
        sendNotifToUsers(DISLIKE, tweets[tweetIndex], toBeNotifiedUsers);
    } else {
        throw UserNotLoggedIn();
    }
}

void SocialNetwork::follow(const string &toBeFollowedUser) {
    if (userIsLoggedIn()) {
        int userIndex = getIndexOfDesiredUser(toBeFollowedUser);
        users[userIndex]->addFollower(currentUser);
    } else {
        throw UserNotLoggedIn();
    }
}

void SocialNetwork::unfollow(const string &toBeUnfollowedUser) {
    if (userIsLoggedIn()) {
        int userIndex = getIndexOfDesiredUser(toBeUnfollowedUser);
        users[userIndex]->deleteFollower(currentUser);
    } else {
        throw UserNotLoggedIn();
    }

}

void SocialNetwork::showNotifications() {
    if (userIsLoggedIn()) {
        currentUser->showNotifications();
    }
}

void SocialNetwork::retweet(const string &tweetId) {
    if (userIsLoggedIn()) {
        string retweetId = determineTweetId();
        int tweetIndex = getIndexOfDesiredTweet(tweetId);
        tweets[tweetIndex]->addRetweet();
        Retweet *newRetweet = new Retweet(retweetId, *tweets[tweetIndex], currentUser);
        vector<User *> toBeMentionedUserRetweet(1, tweets[tweetIndex]->getInvolvedUser());
        tweets.push_back(newRetweet);
        currentUser->addTweet(newRetweet);
        sendNotifToUsers(MENTION, newRetweet, newRetweet->getMentrionedUsers());
        sendNotifToUsers(TWEET, newRetweet, currentUser->getFollowers());
        sendNotifToUsers(RETWEET, newRetweet, toBeMentionedUserRetweet);
    } else {
        throw UserNotLoggedIn();
    }
}

SocialNetwork::~SocialNetwork() {
    for (int i = 0; i < tweets.size(); ++i) {
        delete tweets[i];
    }
    for (int j = 0; j < users.size(); ++j) {
        delete users[j];
    }
}

int SocialNetwork::getIndexByDisplayName(const string &displayName) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getDisplayName() == displayName) {
            return i;
        }
    }
    return INVALID_INDEX;
}

void SocialNetwork::sendNotifToUsers(EventType eventType, string commentId, vector<User *> toBeNotifiedUsers) {
    for (int i = 0; i < toBeNotifiedUsers.size(); ++i) {
        toBeNotifiedUsers[i]->addEvent(eventType, currentUser, commentId);
    }
}


