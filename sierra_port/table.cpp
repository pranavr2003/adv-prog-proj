#include "table.h"

#include <sstream>

// Utility function to clean up attribute spacing
string join_attr(const string& attr) {
    string res = attr;
    size_t pos;

    while ((pos = res.find("  ")) != string::npos) {
        res.replace(pos, 2, " ");
    }

    return res;
}

// Constructor: Opens HTML and CSS files
Table::Table() {
    htmlFile.open("index.html", ios::app);
    cssFile.open("style.css", ios::app);

    if (!htmlFile.is_open()) {
        cerr << "Error: Could not open index.html" << endl;
    }

    if (!cssFile.is_open()) {
        cerr << "Error: Could not open style.css" << endl;
    }
}

// Destructor: Closes HTML and CSS files
Table::~Table() {
    if (htmlFile.is_open()) htmlFile.close();
    if (cssFile.is_open()) cssFile.close();
}

// Creates an HTML table from given headers and rows
void Table::create_table(vector<string> heads, vector<vector<string>> rows, map<string, string> attrs) {
    if (!htmlFile.is_open()) {
        cerr << "Error: Could not write to index.html" << endl;
        return;
    }

    htmlFile << "<table";
    for (const auto& attr : attrs) {
        htmlFile << " " << attr.first << "=\"" << attr.second << "\"";
    }
    htmlFile << ">\n";

    // Table Headers
    htmlFile << "<tr>";
    for (const auto& head : heads) {
        htmlFile << "<th>" << join_attr(head) << "</th>";
    }
    htmlFile << "</tr>\n";

    // Table Rows
    for (const auto& row : rows) {
        htmlFile << "<tr>";
        for (const auto& cell : row) {
            htmlFile << "<td>" << cell << "</td>";
        }
        htmlFile << "</tr>\n";
    }
    htmlFile << "</table>\n";
}

// Reads a CSV file and creates a table from its contents
void Table::get_table(string filename, map<string, string> attrs) {
    ifstream file(filename);
    vector<string> headers;
    vector<vector<string>> rows;
    string line, cell;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    bool first_line = true;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> row;
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        if (first_line) {
            headers = row;
            first_line = false;
        } else {
            rows.push_back(row);
        }
    }
    file.close();

    create_table(headers, rows, attrs);
}

// Writes CSS styles for the table
void Table::css(map<string, string> styles) {
    if (!cssFile.is_open()) {
        cerr << "Error: Could not write to style.css" << endl;
        return;
    }

    cssFile << "table {\n";
    for (const auto& style : styles) {
        cssFile << "\t" << style.first << ": " << style.second << ";\n";
    }
    cssFile << "}\n";
}

// Main function to test the Table class
// int main() {
//     Table table;
//     table.get_table("test.csv", {{"class", "data"}});
//     table.css({{"width", "100%"}, {"border", "1px solid black"}});
//     return 0;
// }
