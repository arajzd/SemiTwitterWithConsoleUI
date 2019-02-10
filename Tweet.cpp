#include "Tweet.h"
#include "Tag.h"


Tweet::Tweet(const string &TweetId, const string &text, User *involvedUser)
        : tweetId(TweetId), text(text),
          involvedUser(involvedUser) { numberOfRetweets = 0; }

void Tweet::addTag(Tag *newTag) {
    tags.push_back(newTag);
}

void Tweet::addMention(User *newMention) {
    mentionedUsers.push_back(newMention);
}

string Tweet::getTweetContentString() {
    string tweetContentString;
    tweetContentString += involvedUser->getDisplayName();
    tweetContentString += LINE_BREAK;
    tweetContentString += text;
    tweetContentString += LINE_BREAK;
    for (int i = 0; i < tags.size(); ++i) {
        tweetContentString += ("#" + tags[i]->getText() + LINE_BREAK);
    }
    for (int j = 0; j < mentionedUsers.size(); ++j) {
        tweetContentString += ("@" + mentionedUsers[j]->getUsername() + LINE_BREAK);
    }
    tweetContentString += "Likes " + to_string(likers.size()) + LINE_BREAK;
    tweetContentString += "Rejeeks " + to_string(numberOfRetweets) + LINE_BREAK;
    return tweetContentString;
}

pair<string, string> Tweet::getTweetIdVsSummaryStringPair() {
    pair<string, string> summaryOfTweetString;
    summaryOfTweetString.first = tweetId;
    summaryOfTweetString.second += (tweetId + " " + involvedUser->getDisplayName() + LINE_BREAK);
    summaryOfTweetString.second += (text + LINE_BREAK);
    return summaryOfTweetString;
}

void Tweet::like(string likerUsername) {
    for (int i = 0; i < likers.size(); ++i) {
        if (likers[i] == likerUsername) {
            return;
        }
    }
    likers.push_back(likerUsername);
    cerr << "number of likers" << likers.size() << endl;
}

void Tweet::dislike(string dislikerUsername) {
    for (int i = 0; i < likers.size(); ++i) {
        if (likers[i] == dislikerUsername) {
            likers.erase(likers.begin() + i);
            return;
        }
    }
}

User *Tweet::getInvolvedUser() {
    return involvedUser;
}

void Tweet::addRetweet() {
    numberOfRetweets++;
}

bool Tweet::hasThisTag(string tagText) {
    for (int i = 0; i < tags.size(); ++i) {
        if (tags[i]->getText() == tagText) {
            return true;
        }
    }
    return false;
}

