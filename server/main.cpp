#include "../utils/utilities.hpp"
#include "server.hpp"
#include "../Interface.h"

using namespace std;

class ClientRequestHandler : public RequestHandler {
protected:
    Interface *interface;
};

class LoginHandler : public ClientRequestHandler {
public:
    explicit LoginHandler(Interface *_interface) { interface = _interface; }

public:
    Response *callback(Request *req) override {
        Response *res = new Response;
        string username = req->getBodyParam("username");
        string password = req->getBodyParam("password");
        cout << "Received Data: " << username << " - " << password << endl;
        srand(time(nullptr));
        string sessionId = to_string(rand());
        res->setSessionId(sessionId);
        try {
            interface->login(username, password, sessionId);
            res->setBody(interface->showHomeHTML(sessionId));
        } catch (const InvalidInputException &invalidInputException) {
            res->setBody(readFile("htmlFiles/login_faulty.html"));
        }
        res->setHeader("Content-Type", "text/html");
        return res;
    }
};

class TweetDetailsHandler : public ClientRequestHandler {
public:
    explicit TweetDetailsHandler(Interface *_interface) { interface = _interface; }

public:
    Response *callback(Request *req) override {
        auto *res = new Response;
        string tweetId = req->getQueryParam("tweetId");
        res->setHeader("Content-Type", "text/html");
        res->setBody(interface->showJeekDetails(req->getSessionId(), tweetId));
        return res;
    }
};

class SignUpHandler : public ClientRequestHandler {
public:
    explicit SignUpHandler(Interface *_interface) { interface = _interface; }

public:
    Response *callback(Request *req) override {
        Response *res = new Response;
        string username = req->getBodyParam("username");
        string displayName = req->getBodyParam("displayName");
        string password = req->getBodyParam("password");
        cout << "Received Data: " << username << " - " << displayName << " -" << password << endl;
        res->setHeader("Content-Type", "text/html");
        try {
            interface->signUp(username, displayName, password);
            res->setBody(readFile("htmlFiles/login.html"));
        } catch (const InvalidInputException &InvalidInputException) {
            res->setBody(readFile("htmlFiles/signup_faulty.html"));
        }
        return res;
    }
};

class LikeHandler : public ClientRequestHandler {
public:
    explicit LikeHandler(Interface *_interface) { interface = _interface; }

public:
    Response *callback(Request *req) override {
        Response *res = new Response;
        string tweetId = req->getQueryParam("tweetId");
        interface->like(tweetId, req->getSessionId());
        res->setHeader("Content-Type", "text/html");
        res->setBody(interface->showJeekDetails(req->getSessionId(), tweetId));
        return res;
    }
};

class DislikeHandler : public ClientRequestHandler {
public:
    explicit DislikeHandler(Interface *_interface) { interface = _interface; }

public:
    Response *callback(Request *req) override {
        Response *res = new Response;
        string tweetId = req->getQueryParam("tweetId");
        interface->dislike(tweetId, req->getSessionId());
        res->setHeader("Content-Type", "text/html");
        res->setBody(interface->showHomeHTML(req->getSessionId()));
        return res;
    }
};

class RetweetHandler : public ClientRequestHandler {
public:
    explicit RetweetHandler(Interface *_interface) { interface = _interface; }

public:
    Response *callback(Request *req) override {
        Response *res = new Response;
        string tweetId = req->getQueryParam("tweetId");
        interface->retweet(tweetId, req->getSessionId());
        res->setHeader("Content-Type", "text/html");
        res->setBody(interface->showHomeHTML(req->getSessionId()));
        return res;
    }
};

class TweetHandler : public ClientRequestHandler {
public:
    explicit TweetHandler(Interface *_interface) { interface = _interface; }

public:
    Response *callback(Request *req) override {
        Response *res = new Response;
        string tweetString = req->getQueryParam("tweetString");
        interface->tweet(tweetString);
        res->setHeader("Content-Type", "text/html");
        res->setBody(interface->showHomeHTML(req->getSessionId()));
        return res;
    }
};

class SearchHandler : public ClientRequestHandler {
public:
    explicit SearchHandler(Interface *_interface) { interface = _interface; }

public:
    Response *callback(Request *req) override {
        Response *res = new Response;
        string searchString = req->getQueryParam("searchString");
        cerr << "search string" << searchString << endl;
        res->setHeader("Content-Type", "text/html");
        if (searchString[0] == '#') {
            res->setBody(interface->showHomeHTML(req->getSessionId(), SEARCH_TAGS, searchString.substr(1)));
            cerr << 5 << endl;
        } else if (searchString[0] == '@') {
            res->setBody(interface->showHomeHTML(req->getSessionId(), SEARCH_USERS, searchString.substr(1)));
            cerr << 6 << endl;
        }
        return res;
    }
};

class LogOutHandler : public ClientRequestHandler {
public:
    explicit LogOutHandler(Interface *_interface) { interface = _interface; }

public:
    Response *callback(Request *req) override {
        Response *res = new Response;
        interface->logOut();
        res->setSessionId("");
        res->setHeader("Content-Type", "text/html");
        res->setBody(readFile("htmlFiles/login.html"));
        return res;
    }
};

int main(int argc, char **argv) {
    try {
        auto *interface = new Interface();
        Server server(argc > 1 ? atoi(argv[1]) : 5000);
        server.get("/", new ShowPage("htmlFiles/initialPage.html"));
        server.get("/home.png", new ShowImage("htmlFiles/home.png"));
        server.get("/home", new ShowPage("htmlFiles/initialPage.html"));
        server.get("/login", new ShowPage("htmlFiles/login.html"));
        server.get("/signup", new ShowPage("htmlFiles/signup.html"));
        server.get("/tweetDetails", new TweetDetailsHandler(interface));
        server.get("/like", new LikeHandler(interface));
        server.get("/dislike", new DislikeHandler(interface));
        server.get("/retweet", new RetweetHandler(interface));
        server.post("/login", new LoginHandler(interface));
        server.get("/search", new SearchHandler(interface));
        server.post("/signup", new SignUpHandler(interface));
        server.get("/logout", new LogOutHandler(interface));
        server.run();
    } catch (Server::Exception e) {
        cout << "SSS" << endl;
        cout << e.getMessage() << endl;
    }
}
