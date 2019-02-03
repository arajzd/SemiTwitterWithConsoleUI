
#include "Comment.h"

void Comment::print() {
    cout << involvedUserDisplayName << endl;
    cout << text << endl;
    if (!replies.empty()) {
        cout << "Replies:" << endl;
    }
    for (int i = 0; i < replies.size(); ++i) {
        cout << replies[i].getReplyId() << endl;
    }
}

void Comment::addThisReply(string replyText, string involvedUserDisplayName, Comment *involvedComment) {
    string replyId2 = commentId + "." + to_string(replies.size());
    Reply *newReply = new Reply(replyId2, replyText, involvedUserDisplayName, involvedComment);
    replies.push_back(*newReply);
}

void Comment::printThisReply(const string &replyId) {
    for (int i = 0; i < replies.size(); ++i) {
        if (replies[i].getReplyId() == replyId || replies[i].hasThisReply(replyId)) {
            replies[i].printThisReply(replyId);
        }
    }
}

bool Comment::hasThisReply(const string &replyId) {
    for (int i = 0; i < replies.size(); ++i) {
        if (replies[i].getReplyId() == replyId || replies[i].hasThisReply(replyId)) {
            return true;
        }
    }
    return false;
}

void Comment::addThisReplyToReply(string replyId, string replyText, string involvedUserDisplayName) {
    for (int i = 0; i < replies.size(); ++i) {
        if (replies[i].getReplyId() == replyId) {
            replies[i].addThisReplyToReply(replyId, replyText, involvedUserDisplayName, &replies[i]);
        }
    }
}

const string &Comment::getInvolvedUserDisplayName() const {
    return involvedUserDisplayName;
}
