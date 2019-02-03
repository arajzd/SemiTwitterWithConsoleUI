
#ifndef FINALPROJECT_UTILS_H
#define FINALPROJECT_UTILS_H


#define MAX_WORD_LIMIT 140
#define INVALID_INDEX (-1)

class Exception {
public:
    virtual const char *what() const =0;
};

class InvalidInputException : public Exception {
public:
    virtual const char *what() const { return "invalid input"; }
};

class InvalidUserNameAndPassword : public InvalidInputException {
public:
    const char *what() const { return "invalid username and pass"; }
};

class TextExceedsMaxWordLimit : InvalidInputException {
};

class UsernameAlreadyExists : public InvalidInputException {
public:
    const char *what() const { return "username already exists"; }
};

class UserNotLoggedIn : public InvalidInputException {

};

class UserDidNotLikeTweet : public InvalidInputException {

};

class UnknownEventException {

};

#endif //FINALPROJECT_UTILS_H
