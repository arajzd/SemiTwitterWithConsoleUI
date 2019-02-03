
#include "Event.h"
#include "User.h"
#include "Tweet.h"


void Event::print() {
    switch (eventType) {
        case LIKE : {
            cout << involvedUser->getUsername() << " liked " << involvedTweet->getTweetId() << endl;
            break;
        }
        case DISLIKE : {
            cout << involvedUser->getUsername() << " disliked " << involvedTweet->getTweetId() << endl;
            break;
        }
        case MENTION : {
            cout << involvedUser->getUsername() << " mentioned you in " << involvedTweet->getTweetId() << endl;
            break;
        }
        case COMMENT : {
            cout << involvedUser->getUsername() << " commented on " << involvedTweet->getTweetId() << endl;
            break;
        }
        case REPLY : {
            cout << involvedUser->getUsername() << " replied " << commentId << endl;
            break;
        }
        case TWEET : {
            cout << involvedUser->getUsername() << " jeeked " << involvedTweet->getTweetId() << endl;
            break;
        }
        case RETWEET : {
            cout << involvedUser->getUsername() << " rejeeked " << involvedTweet->getTweetId() << endl;
        }
        default:
        {
            return;
        }
    }
}
