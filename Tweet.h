
#include <string>
#include <vector>
#include "User.h"
#include "utils.h"
#include "Comment.h"
#include <iostream>

#ifndef FINALPROJECT_TWEET_H
#define FINALPROJECT_TWEET_H

using namespace std;

class Retweet;

class Tag;

class Tweet {
protected:
    string TweetId;
    string text;
    User *involvedUser;
    vector<Tag *> tags;
    vector<User *> mentionedUsers;
    vector<string> likers;
    int numberOfRetweets;
    vector<Comment *> comments;

public:

    Tweet(const string &TweetId, const string &text, User *involvedUser);


    const string &getTweetId() const { return TweetId; }

    virtual void printTweet();

    virtual void printBriefly();

    void addComment(string text, string involvedUserDisplayName);

    void addThisReply(string replyText, string commentId, string involvedUserDisplayName);

    void addTag(Tag *newTag);

    void addMention(User *newMention);

    void addThisReplyToReply(string replyText, string replyId, string involvedUserDisplayName);

    void like(string likerUsername);

    void dislike(string dislikerUsername);

    User *getInvolvedUser() const;

    bool hasThisTag(string tagText);

    void addRetweet();

    bool CommentsHaveThisReply(string replyId);

    bool hasThisComment(string commentId);

    string getThisCommentsUser(const string &commentId) ;

    void printThisComment(string commentId);

    void printThisReply(string replyId);
};


#endif //FINALPROJECT_TWEET_H
