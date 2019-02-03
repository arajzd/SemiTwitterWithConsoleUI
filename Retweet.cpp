

#include "Retweet.h"
#include "Tag.h"
void Retweet::printTweet() {
    cout << involvedUser->getDisplayName() << endl;
    cout << "Rejeeked: " << text << endl;
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

void Retweet::printBriefly() {
    cout << getTweetId() << " " << involvedUser->getDisplayName() << endl;
    cout << "Rejeeked: ";
    cout << text << endl;
}
