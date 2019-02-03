
#include "Reply.h"

void Reply::printThisReply(const string &replyId) const{
    if (Reply::replyId == replyId) {
        cout << involvedUserDisplayName << endl;
        cout << replyText << endl;
        if (!replies.empty()) {
            cout << "Replies:" << endl;
            for (int i = 0; i < replies.size(); ++i) {
                cout << replies[i]->getReplyId() << endl;
            }
        }
    } else if (this->hasThisReply(replyId)) {
        for (int i = 0; i < replies.size(); ++i) {
            if (replies[i]->getReplyId() == replyId) {
                replies[i]->printThisReply(replyId);
            }
        }
    }
}

bool Reply::hasThisReply(const string &replyId) const{
    for (int i = 0; i < replies.size(); ++i) {
        if (replies[i]->getReplyId() == replyId) {
            return true;
        }
    }
    return false;
}

void Reply::addThisReplyToReply(string replyId, string replyText, string involvedUserDisplayName, Reply *reply) {
    string newReplyId = replyId + "." + to_string(replies.size());
    Reply *newReply = new Reply(newReplyId, replyText, involvedUserDisplayName, reply);
    replies.push_back(newReply);
}
