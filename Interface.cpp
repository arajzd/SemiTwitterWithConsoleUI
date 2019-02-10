#include "SocialNetwork.h"


void Interface::signUp(const string &username, const string &displayName, const string &password) {
    socialNetwork->signUp(username, displayName, password);
}

void Interface::login(const string &username, const string &password, const string &sessionId) {
    sessionIdVsUsername[sessionId] = username;
    socialNetwork->login(username, password);
}

void Interface::logOut() {
    socialNetwork->logOut();
}

void Interface::tweet(string tweetString) {
    string input, text;
    vector<string> tags, mentions;
    auto inputVector = Interface::parseInput(tweetString);
    for (int i = 0; i < inputVector.size(); i++) {
        if (inputVector[i] == "text") {
            while ((inputVector[i + 1] != "tag") || (inputVector[i + 1] != "mention")) {
                text += inputVector[i + 1];
                i++;
                if (text.size() > MAX_WORD_LIMIT) {
                    throw TextExceedsMaxWordLimit();
                }
            }
        } else if (inputVector[i] == "tag") {
            tags.push_back(inputVector[i + 1]);
        } else if (input == "mention") {
            mentions.push_back(inputVector[i + 1]);
        }
    }
    socialNetwork->tweet(text, tags, mentions);
}

void Interface::like(const string &tweetId, const string &sessionId) {
    if (isSessionIdValid(sessionId)) {
        login(sessionIdVsUsername[sessionId]);
        socialNetwork->like(tweetId);
        logOut();
    }
}

void Interface::dislike(const string &tweetId, const string &sessionId) {
    if (isSessionIdValid(sessionId)) {
        login(sessionIdVsUsername[sessionId]);
        socialNetwork->dislike(tweetId);
        logOut();
    }
}

void Interface::retweet(const string &toBeRetweetedId, const string &sessionId) {
    if (isSessionIdValid(sessionId)) {
        login(sessionIdVsUsername[sessionId]);
        socialNetwork->retweet(toBeRetweetedId);
        logOut();
    }
}

string Interface::showHomeHTML(const string &sessionId, HomePageType homePageType, const string &searchString) {
    auto currentUser = sessionIdVsUsername[sessionId];
    string userTweetsHTML;
    cerr << 1 << endl;
    if (isSessionIdValid(sessionId)) {
        login(currentUser);
        vector<pair<string, string> > relatedTweets;
        userTweetsHTML += getHomeDefaultPage();
        if (homePageType == DEFAULT) {
            relatedTweets = socialNetwork->showUserTweets(currentUser);
        } else if (homePageType == SEARCH_TAGS) {
            relatedTweets = socialNetwork->searchForTags(searchString);
        } else if (homePageType == SEARCH_USERS) {
            relatedTweets = socialNetwork->showUserTweets(searchString);
        }
        cerr << 2 << endl;
        cerr << " size of related tweets" << relatedTweets.size() << endl;
        for (int i = 0; i < relatedTweets.size(); ++i) {
            userTweetsHTML += relatedTweets[relatedTweets.size() - i - 1].second;
            userTweetsHTML += "<a href=\"/tweetDetails?tweetId=" +
                              relatedTweets[relatedTweets.size() - i - 1].first +
                              "\">MORE DETAILS</a>" + LINE_BREAK + LINE_BREAK;
        }
        userTweetsHTML += "</div>\n</body>\n</html>";
        cerr << 3 << endl;
        logOut();
    }
    cerr << endl;
    return userTweetsHTML;
}

string Interface::showJeekDetails(const string &sessionId, const string &tweetId) {
    string tweetDetails;
    if (isSessionIdValid(sessionId)) {
        login(sessionIdVsUsername[sessionId]);
        tweetDetails += "<!DOCTYPE html>\n"
                "<html>\n"
                "<body>";
        tweetDetails += "Hi " + socialNetwork->getCurrentUserDisplayName() + "!" LINE_BREAK;
        tweetDetails += "<a href=\"/logout\">LOGOUT</a>" LINE_BREAK;
        tweetDetails += socialNetwork->showTweet(tweetId);
        tweetDetails += LINE_BREAK
                                "<a href=\"/like?tweetId=" + tweetId + "\">LIKE</a>\n"
                                LINE_BREAK
                                "<a href=\"/dislike?tweetId=" + tweetId + "\">DISLIKE</a>\n"
                                LINE_BREAK
                                "<a href=\"/retweet?tweetId=" + tweetId + "\">RETWEET</a>\n";
        tweetDetails += "</body>"
                "</html>";
        logOut();
    }
    return tweetDetails;
}

vector<string> Interface::parseInput(const string &inputString) {
    istringstream iss(inputString);
    vector<string> input_vector;
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(input_vector));
    return input_vector;
}

string Interface::getHomeDefaultPage() {
    return ("<!DOCTYPE html>\n"
                    "<html>\n"
                    "<body style=\"text-align: center;\">\n"
                    "Hi " + socialNetwork->getCurrentUserDisplayName() + "!"
                    "<div align=\"right\">\n"
                    "    <a href=\"/logout\">LOG OUT</a>\n"
                    "</div>\n"

                    "<div style=\"padding-left:16px\" align=\"center\">\n"
                    "    <form action=\"/search\" method=\"get\">\n"
                    "        <input type=\"text\" placeholder=\"Search...\" name=\"searchString\">\n"
                    "        <button type=\"submit\">Search</button>\n"
                    "    </form>\n"
                    "</div>\n"
                    "<div align=\"left\">\n");
}

void Interface::login(const string &username) {
    socialNetwork->login(username);
}

Interface::Interface() {
    unique_ptr<SocialNetwork> _socialNetwork(new SocialNetwork());
    socialNetwork = move(_socialNetwork);
}

