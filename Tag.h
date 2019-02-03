
#include <string>
#include <vector>

#ifndef FINALPROJECT_TAG_H
#define FINALPROJECT_TAG_H

class Tweet;

using namespace std;

class Tag {
    string text;
public:
    explicit Tag(const string &text) : text(text) {}

    bool operator==(const Tag &rhs) const;

    const string &getText() const { return text; }
};


#endif //FINALPROJECT_TAG_H
