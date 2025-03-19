#include "custom_tags.h"

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

// string join_attr(const vector<string>& attrs) {
//     string result;
//     for (const auto& item : attrs) {
//         result += item + " ";
//     }
//     return result;
// }

ofstream Tag::file;

Tag::Tag(string tagName, map<string, string> attrs, string text)
    : name(tagName), attributes(attrs), content(text) {
    if (!file.is_open()) {
        file.open("index.html", ios::app);
        if (!file) {
            cerr << "Error opening file!" << endl;
            exit(1);
        }
    }
}

Tag::~Tag() {
    if (file.is_open()) {
        file.close();
    }
}

void Tag::render() {
    file << "<" << name;
    for (const auto& attr : attributes) {
        file << " " << attr.first << "=\"" << attr.second << "\"";
    }
    file << ">" << content << "</" << name << ">";
}

CmTag::CmTag(string tagName, map<string, string> attrs) : Tag(tagName, attrs) {}

void CmTag::enter() {
    file << "<" << name;
    for (const auto& attr : attributes) {
        file << " " << attr.first << "=\"" << attr.second << "\"";
    }
    file << ">" << endl;
}

void CmTag::exit() {
    file << "</" << name << ">" << endl;
}

// int main() {
    // Tag div("div", { {"class", "container"}, {"id", "main"} });
    // Tag p("p", {}, "Hello, World!");
    // CmTag section("section", { {"class", "wrapper"}, {"style", "color: pink; background-color: yellow"} });
    
    // section.enter();
    // div.render();
    // p.render();
    // section.exit();
    
//     return 0;
// }