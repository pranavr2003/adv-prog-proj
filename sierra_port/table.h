#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Table {
public:
    ofstream htmlFile, cssFile;

    Table();
    ~Table();
    void create_table(vector<string> heads, vector<vector<string>> rows, map<string, string> attrs = {});
    void get_table(string filename, map<string, string> attrs = {});
    void css(map<string, string> styles);
};

#endif // TABLE_H
