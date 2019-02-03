#include "User.h"
#include "Tweet.h"

void User::addEvent(EventType eventType, User *involvedUser, Tweet *involvedTweet) {
    Event *newEvent = new Event(eventType, involvedUser, involvedTweet);
    notifications.push_back(*newEvent);
}

void User::printListOfTweets() {
    for (int i = 0; i < tweets.size(); ++i) {
        tweets[i]->printBriefly();
        cout << endl;
    }
}

void User::addTweet(Tweet *newTweet) {
    tweets.push_back(newTweet);
}

bool User::operator==(const User &rhs) const {
    return username == rhs.username;
}

void User::addFollower(User *toBeFollowedUser) {
    for (int i = 0; i < followers.size(); ++i) {
        if (*followers[i] == *toBeFollowedUser) {
            return;
        }
    }
    followers.push_back(toBeFollowedUser);
}

void User::deleteFollower(User *toBeUnfollowedUser) {
    for (int i = 0; i < followers.size(); ++i) {
        if (*followers[i] == *toBeUnfollowedUser) {
            followers.erase(followers.begin() + i);
            return;
        }
    }
}

void User::showNotifications() {
    for (int i = 0; i < notifications.size(); ++i) {
        notifications[i].print();
    }
    notifications.clear();
}

void User::addEvent(EventType eventType, User *involvedUser, string involvedCommentId) {
    Event *newEvent = new Event(eventType, involvedUser, involvedCommentId);
    notifications.push_back(*newEvent);
}

