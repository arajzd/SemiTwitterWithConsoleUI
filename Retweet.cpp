

#include "Retweet.h"
#include "Tag.h"

string Retweet::getTweetContentString() {
    string tweetString;
    tweetString += involvedUser->getDisplayName() + LINE_BREAK;
    tweetString += "Rejeeked: " + text + LINE_BREAK;
    for (int i = 0; i < tags.size(); ++i) {
        tweetString += "#" + tags[i]->getText() + LINE_BREAK;
    }
    for (int j = 0; j < mentionedUsers.size(); ++j) {
        tweetString += "@" + mentionedUsers[j]->getUsername() + LINE_BREAK;
    }
    tweetString += "Likes " + to_string(likers.size()) + LINE_BREAK;
    tweetString += "Rejeeks " + to_string(numberOfRetweets) + LINE_BREAK;
    return tweetString;
}

pair<string, string> Retweet::getTweetIdVsSummaryStringPair() {
    pair<string,string> tweetIdVsSummaryStringPair;
    tweetIdVsSummaryStringPair.first=tweetId;
    tweetIdVsSummaryStringPair.second+= tweetId + " " + involvedUser->getDisplayName() +LINE_BREAK;
    tweetIdVsSummaryStringPair.second+= "Rejeeked: "+ text + LINE_BREAK;
    return tweetIdVsSummaryStringPair;
}
