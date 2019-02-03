#include <vector>
#include <string>
#include "User.h"

#ifndef FINALPROJECT_REPLY_H
#define FINALPROJECT_REPLY_H
using namespace std;

class Comment;

class Reply {
    string replyId;
    string replyText;
    Comment *comment;
    Reply *reply;
    string involvedUserDisplayName;
    vector<Reply *> replies;
public:
    Reply(const string &replyId, const string &replyText, const string &involvedUserDisplayName, Comment *comment)
            : replyId(replyId),  replyText(replyText), comment(comment),
              involvedUserDisplayName(involvedUserDisplayName) {}

    Reply(const string &replyId, const string &replyText, const string &involvedUserDisplayName, Reply *reply)
            : replyId(replyId),replyText(replyText), reply(reply), involvedUserDisplayName(involvedUserDisplayName) {}

    void addThisReplyToReply(string replyId, string replyText, string involvedUserDisplayName, Reply *reply);

    void printThisReply(const string &replyId) const;

    bool hasThisReply(const string &replyId) const;

    const string &getReplyId() const { return replyId; }

    const string &getReplyText() const {
        return replyText;
    }
};


#endif
