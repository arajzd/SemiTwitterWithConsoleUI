#include <vector>
#include <string>
#include <iostream>
#include "Event.h"
#include "utils.h"

#ifndef FINALPROJECT_USER_H
#define FINALPROJECT_USER_H

using namespace std;

class Tweet;

class User {
    string username;
    string displayName;
    vector<User *> followers;
    vector<Tweet *> tweets;
    vector<Event> notifications;
public:
    const vector<User *> &getFollowers() const {
        return followers;
    }

public:
    User(const string &username, const string &displayName) : username(username), displayName(
            displayName) {}

    void addEvent(EventType eventType, User *involvedUser, Tweet *involvedTweet);

    void addEvent(EventType eventType, User *involvedUser, string involvedCommentId);

    void addTweet(Tweet *newTweet);

    void printListOfTweets();

    void addFollower(User *toBeFollowedUser);

    void showNotifications();

    void deleteFollower(User *toBeUnfollowedUser);

    const string &getUsername() const { return username; }

    const string &getDisplayName() const { return displayName; }

    bool operator==(const User &rhs) const;

};


#endif //FINALPROJECT_USER_H
