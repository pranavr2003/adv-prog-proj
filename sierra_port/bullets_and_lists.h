#ifndef BULLETS_AND_LISTS_H
#define BULLETS_AND_LISTS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

class Bullets {
public:
    Bullets(bool ul, vector<string> points, map<string, string> kwargs = {});

    void enter();
    void exit();

private:
    bool ul;
    vector<string> points;
    map<string, string> kwargs;
    stringstream html;

    void writeToFile();
};

#endif // BULLETS_AND_LISTS_H
