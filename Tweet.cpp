
#include "Tweet.h"
#include "Tag.h"

Tweet::Tweet(const string &TweetId, const string &text, User *involvedUser)
        : TweetId(TweetId), text(text),
          involvedUser(involvedUser) { numberOfRetweets = 0; }

void Tweet::addTag(Tag *newTag) {
    tags.push_back(newTag);
}

void Tweet::addMention(User *newMention) {
    mentionedUsers.push_back(newMention);
}

void Tweet::printTweet() {
    cout << involvedUser->getDisplayName() << endl;
    cout << text << endl;
    for (int i = 0; i < tags.size(); ++i) {
        cout << "#" << tags[i]->getText() << endl;
    }
    for (int j = 0; j < mentionedUsers.size(); ++j) {
        cout << "@" << mentionedUsers[j]->getUsername() << endl;
    }
    cout << "Likes " << likers.size() << endl;
    cout << "Rejeeks " << numberOfRetweets << endl;
    if (!comments.empty()) {
        cout << "comments:" << endl;
    }
    for (int k = 0; k < comments.size(); ++k) {
        cout << comments[k]->getCommentId() << endl;
    }

}

void Tweet::printBriefly() {
    cout << TweetId << " " << involvedUser->getDisplayName() << endl;
    cout << text << endl;
}

void Tweet::addComment(string text, string involvedUserDisplayName) {
    string commentId = TweetId + "." + to_string(comments.size());
    Comment *newComment = new Comment(text, commentId, involvedUserDisplayName);
    comments.push_back(newComment);
}

bool Tweet::hasThisComment(string commentId) {
    for (int i = 0; i < comments.size(); ++i) {
        if (comments[i]->getCommentId() == commentId) {
            return true;
        }
    }
    return false;
}

void Tweet::printThisComment(string commentId) {
    for (int i = 0; i < comments.size(); ++i) {
        if (comments[i]->getCommentId() == commentId) {
            comments[i]->print();
        }
    }
}

void Tweet::addThisReply(string replyText, string commentId, string involvedUserDisplayName) {
    for (int i = 0; i < comments.size(); ++i) {
        if (comments[i]->getCommentId() == commentId) {
            string replyId = comments[i]->getCommentId() + "." + to_string(comments.size() - 1);
            comments[i]->addThisReply(replyText, involvedUserDisplayName, comments[i]);
            return;
        }
    }
}

void Tweet::printThisReply(string replyId) {
    for (int i = 0; i < comments.size(); ++i) {
        if (comments[i]->hasThisReply(replyId)) {
            comments[i]->printThisReply(replyId);
            return;
        }
    }
}

void Tweet::addThisReplyToReply(string replyText, string replyId, string involvedUserDisplayName) {
    for (int i = 0; i < comments.size(); ++i) {
        if (comments[i]->hasThisReply(replyId)) {
            comments[i]->addThisReplyToReply(replyId, replyText, involvedUserDisplayName);
        }
    }
}

bool Tweet::CommentsHaveThisReply(string replyId) {
    for (int i = 0; i < comments.size(); ++i) {
        if (comments[i]->hasThisReply(replyId)) {
            return true;
        }
    }
    return false;
}

void Tweet::like(string likerUsername) {
    for (int i = 0; i < likers.size(); ++i) {
        if (likers[i] == likerUsername) {
            return;
        }
    }
    likers.push_back(likerUsername);
}

void Tweet::dislike(string dislikerUsername) {
    for (int i = 0; i < likers.size(); ++i) {
        if (likers[i] == dislikerUsername) {
            likers.erase(likers.begin() + i);
            return;
        }
    }
   throw UserDidNotLikeTweet();
}

User *Tweet::getInvolvedUser() const {
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

string Tweet::getThisCommentsUser(const string &commentId) {
    for (int i = 0; i <comments.size() ; ++i) {
        if(comments[i]->getCommentId() == commentId){
            return comments[i]->getInvolvedUserDisplayName();
        }
    }
}

