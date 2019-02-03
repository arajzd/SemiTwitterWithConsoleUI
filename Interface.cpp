
#include "Interface.h"


void Interface::signUp() {
    string username, displayName, password;
    cin >> username >> displayName >> password;
    socialNetwork->signUp(username, displayName, password);
}

void Interface::login() {
    string username, password;
    cin >> username >> password;
    socialNetwork->login(username, password);
}


void Interface::logOut() {
    socialNetwork->logOut();
}

void Interface::tweet() {
    string input, text;
    vector<string> tags, mentions;
    while (cin >> input) {
        if (input == "text") {
            text.clear();
            cin.ignore(1);
            getline(cin, text);
            cin.clear();
            if (text.size() > MAX_WORD_LIMIT) {
                throw TextExceedsMaxWordLimit();
            }
        } else if (input == "tag") {
            cin >> input;
            tags.push_back(input);
        } else if (input == "mention") {
            cin >> input;
            mentions.push_back(input);
        } else if (input == "abort") {
            return;
        } else if (input == "publish") {
            break;
        }
    }
    socialNetwork->tweet(text, tags, mentions);
}

void Interface::showTweet() {
    string tweetId;
    cin >> tweetId;
    socialNetwork->showTweet(tweetId);
}

void Interface::showUserTweets() {
    string username;
    cin >> username;
    socialNetwork->showUserTweets(username);
}

void Interface::searchForTags() {
    string tagText;
    cin >> tagText;
    socialNetwork->searchForTags(tagText);
}

void Interface::comment() {
    string tweetId, commentText;
    cin >> tweetId;
    cin.ignore(1);
    getline(cin, commentText);
    socialNetwork->comment(tweetId, commentText);
}

void Interface::showComment() {
    string commentId;
    cin >> commentId;
    socialNetwork->showComment(commentId);
}

void Interface::replyTheComment(string commentId) {
    string replyText;
    cin.ignore(1);
    getline(cin, replyText);
    socialNetwork->replyTheComment(commentId, replyText);
}

void Interface::showReply() {
    string replyId;
    cin >> replyId;
    socialNetwork->showReply(replyId);
}

void Interface::replyTheReply(string replyId) {
    string replyText;
    cin.ignore(1);
    getline(cin, replyText);
    socialNetwork->replyTheReply(replyId, replyText);
}

void Interface::like() {
    string likedTweetId;
    cin >> likedTweetId;
    socialNetwork->like(likedTweetId);
}

void Interface::dislike() {
    string dislikedTweetId;
    cin >> dislikedTweetId;
    socialNetwork->dislike(dislikedTweetId);
}

void Interface::follow() {
    string toBeFollowedUser;
    cin >> toBeFollowedUser;
    socialNetwork->follow(toBeFollowedUser);
}

void Interface::unfollow() {
    string toBeFollowedUser;
    cin >> toBeFollowedUser;
    socialNetwork->unfollow(toBeFollowedUser);
}

void Interface::showNotifications() {
    socialNetwork->showNotifications();
}

void Interface::retweet() {
    string toBeRetweetedId;
    cin >> toBeRetweetedId;
    socialNetwork->retweet(toBeRetweetedId);
}

void Interface::getInput() {
    string choice;
    while (cin >> choice) {
        try {
            if (choice == "signup") {
                signUp();
                cerr << "signed up" << endl;
            } else if (choice == "login") {
                login();
                cerr << "logged in " << endl;
            } else if (choice == "logout") {
                logOut();
                cerr << "logged out " << endl;
            } else if (choice == "jeek") {
                tweet();
                cerr << "tweeted !" << endl;
            } else if (choice == "showJeek") {
                showTweet();
            } else if (choice == "search") {
                cin.ignore();
                char inputChar = (char) getchar();
                if (inputChar == '@') {
                    showUserTweets();
                } else if (inputChar == '#') {
                    searchForTags();
                }
                cerr << "search complete !" << endl;
            } else if (choice == "comment") {
                comment();
                cerr << "commented!" << endl;
            } else if (choice == "reply") {
                string toBeRepliedId;
                cin >> toBeRepliedId;
                string idType = isReplyIdOrCommentId(toBeRepliedId);
                if (idType == "commentId") {
                    replyTheComment(toBeRepliedId);
                } else if (idType == "replyId") {
                    replyTheReply(toBeRepliedId);
                }
                cerr << "replied!" << endl;
            } else if (choice == "showComment") {
                showComment();
                cerr << "comment shown" << endl;
            } else if (choice == "rejeek") {
                retweet();
                cerr << "retweeted!" << endl;
            } else if (choice == "showReply") {
                showReply();
                cerr << "reply shown!" << endl;
            } else if (choice == "like") {
                like();
                cerr << "liked!" << endl;
            } else if (choice == "dislike") {
                dislike();
                cerr << "disliked!" << endl;
            } else if (choice == "follow") {
                follow();
                cerr << "followed!" << endl;
            } else if (choice == "unfollow") {
                unfollow();
                cerr << "unfollowed!" << endl;
            } else if (choice == "notifications") {
                showNotifications();
                cerr << "notifications shown!" << endl;
            } else {
                throw InvalidInputException();
            }
            cin.clear();
        } catch (...) {
            cin.clear();
            continue;
        }
    }
}


string Interface::isReplyIdOrCommentId(string Id) {
    int count = 0;
    std::size_t found = Id.find('.');
    while (found != std::string::npos) {
        found++;
        found = Id.find('.', found);
        count++;
    }
    if (count == 1) {
        return "commentId";
    } else if (count > 1) {
        return "replyId";
    } else {
        throw InvalidInputException();
    }
}

