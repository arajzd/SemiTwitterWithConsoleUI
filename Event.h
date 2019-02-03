
#include <iostream>

#ifndef FINALPROJECT_EVENT_H
#define FINALPROJECT_EVENT_H


class User;

class Tweet;

class Comment;
using namespace std;
enum EventType {
    LIKE, DISLIKE, COMMENT, REPLY, TWEET, MENTION, RETWEET
};

class Event {
    EventType eventType;
    User *involvedUser;
    Tweet *involvedTweet;
    string commentId;
public:
    Event(EventType eventType, User *involvedUser, Tweet *involvedTweet) : eventType(eventType),
                                                                                  involvedUser(involvedUser),
                                                                                  involvedTweet(involvedTweet) {}

    Event(EventType eventType, User *involvedUser, const string &commentId) : eventType(eventType),
                                                                              involvedUser(involvedUser),
                                                                              commentId(commentId) {}

    void print();

};


#endif //FINALPROJECT_EVENT_H
