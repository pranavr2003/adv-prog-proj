#ifndef TAGS_H
#define TAGS_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

string join_attr(const vector<string>& attrs);

class Tag {
protected:
    static ofstream file;

public:
    string name;
    map<string, string> attributes;
    string content;

    Tag(string tagName, map<string, string> attrs = {}, string text = "");
    virtual ~Tag();
    virtual void render();
};

class CmTag : public Tag {
public:
    CmTag(string tagName, map<string, string> attrs = {});
    void enter();
    void exit();
};

#endif // TAGS_H