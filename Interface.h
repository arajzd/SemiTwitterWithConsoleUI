#include "SocialNetwork.h"
#include "utils.h"
#include <iostream>

#ifndef FINALPROJECT_INTERFACE_H
#define FINALPROJECT_INTERFACE_H


class Interface {
private:
    SocialNetwork *socialNetwork;
public:
    Interface() { socialNetwork = new SocialNetwork(); }

    ~Interface() { delete socialNetwork; }

    void getInput();

    void signUp();

    void login();

    void tweet();

    void comment();

    void retweet();

    void replyTheComment(string commentId);

    void showReply();

    void replyTheReply(string replyId);

    void like();

    void follow();

    void unfollow();

    void showNotifications();

    void dislike();

    void searchForTags();

    void showComment();

    void showTweet();

    void showUserTweets();

    void logOut();

    static string isReplyIdOrCommentId(string Id);

};


#endif
