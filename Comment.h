
#include "Reply.h"
#include "User.h"
#include <vector>
#include <string>

using namespace std;
#ifndef FINALPROJECT_COMMENT_H
#define FINALPROJECT_COMMENT_H


class Tweet;

class Comment {
    string text;
    string commentId;
    string involvedUserDisplayName;
    vector<Reply> replies;
public:
    Comment(const string &text, const string &commentId, const string &involvedUserDisplayName) :
            text(text), commentId(commentId), involvedUserDisplayName(involvedUserDisplayName) {}

    const string &getCommentId() const { return commentId; }

    bool hasThisReply(const string &replyId);

    void addThisReply(string replyText, string involvedUserDisplayName, Comment *involvedComment);

    void addThisReplyToReply(string replyId, string replyText, string involvedUserDisplayName);

    const string &getInvolvedUserDisplayName() const;

    void printThisReply(const string &replyId);

    void print();
};


#endif
