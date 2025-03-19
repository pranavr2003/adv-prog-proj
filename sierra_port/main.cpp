#include "table.h"
#include "custom_tags.h"
#include "bullets_and_lists.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

void title(const string& Title, const string& icon = "") {
    ofstream htmlFile("index.html", ios::trunc);
    htmlFile << "<!doctype html>\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n<title>" << Title << "</title>\n<link rel=\"stylesheet\" href=\"style.css\">";
    if (!icon.empty() && icon.substr(icon.find_last_of(".") + 1) == "ico") {
        htmlFile << "\n<link rel=\"shortcut icon\" href=\"" << icon << "\">";
    }
    htmlFile << "\n</head>\n<body>\n";
    htmlFile.close();
    ofstream cssFile("style.css", ios::trunc);
    cssFile.close();
}

void addFont(const string& font_link) {
    ofstream htmlFile("index.html", ios::app);
    htmlFile << "\n<link href=\"" << font_link << "\" rel=\"stylesheet\">";
    htmlFile.close();
}

void head(const string& Head, const string& type = "h1", map<string, string> styles = {}) {
    ofstream htmlFile("index.html", ios::app);
    htmlFile << "\n<" << type << ">" << Head << "</" << type << ">";
    htmlFile.close();
    
    if (!styles.empty()) {
        ofstream cssFile("style.css", ios::app);
        cssFile << "\n\n" << type << " {";
        for (const auto& style : styles) {
            cssFile << "\n\t" << style.first << ": " << style.second << ";";
        }
        cssFile << "\n}";
        cssFile.close();
    }
}

string join_attr(const vector<string>& elements) {
    string result;
    for (const auto& item : elements) {
        result += item + " ";
    }
    while (result.find("  ") != string::npos) {
        result.replace(result.find("  "), 2, " ");
    }
    return result;
}

class Image {
public:
    string src;
    map<string, string> attributes;

    Image(const string& src, map<string, string> attrs = {}) : src(src), attributes(attrs) {}

    void show() {
        ofstream htmlFile("index.html", ios::app);
        htmlFile << "\n<img src=\"" << src << "\"";
        for (const auto& attr : attributes) {
            htmlFile << " " << attr.first << "=\"" << attr.second << "\"";
        }
        htmlFile << ">";
        htmlFile.close();
    }

    void css(map<string, string> styles) {
        ofstream cssFile("style.css", ios::app);
        cssFile << "\n\nimg {";
        for (const auto& style : styles) {
            cssFile << "\n\t" << style.first << ": " << style.second << ";";
        }
        cssFile << "\n}";
        cssFile.close();
    }
};

string indent(int level) {
    return string(level * 4, ' ');  // 4 spaces per indentation level
}

// Function to prettify HTML and auto-close unclosed tags
void autoPrettify() {
    ifstream inputFile("index.html");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open index.html\n";
        return;
    }

    string line;
    string formattedHtml;
    stack<string> tagStack;
    unordered_map<string, bool> selfClosingTags = {
        {"meta", true}, {"link", true}, {"br", true}, {"img", true}, {"input", true}, {"hr", true}
    };
    
    int indentLevel = 0;
    regex openTag(R"(<([a-zA-Z1-6]+)(\s*[^>]*)>)");  // Matches opening tags
    regex closeTag(R"(</([a-zA-Z1-6]+)>)");           // Matches closing tags
    regex selfClosingTag(R"(<([a-zA-Z1-6]+)(\s*[^>]*)/>)"); // Matches self-closing tags

    while (getline(inputFile, line)) {
        line = regex_replace(line, regex("^\\s+|\\s+$"), ""); // Trim spaces

        smatch match;
        if (regex_match(line, match, openTag)) {
            string tagName = match[1];

            // If it's NOT a self-closing tag, push to stack
            if (selfClosingTags.find(tagName) == selfClosingTags.end()) {
                tagStack.push(tagName);
            }
        } 
        else if (regex_match(line, match, closeTag)) {
            // If it's a closing tag, pop from stack
            if (!tagStack.empty() && tagStack.top() == match[1]) {
                tagStack.pop();
            } 
            else {
                // If stack is empty or mismatched, auto-close previous tag
                if (!tagStack.empty()) {
                    formattedHtml += indent(indentLevel--) + "</" + tagStack.top() + ">\n";
                    tagStack.pop();
                }
            }
        }

        formattedHtml += indent(indentLevel) + line + "\n";

        // Increase indent level after an opening tag (not self-closing)
        if (regex_match(line, openTag) && !regex_match(line, selfClosingTag)) {
            indentLevel++;
        }
    }

    inputFile.close();

    // Auto-close any remaining unclosed tags
    while (!tagStack.empty()) {
        formattedHtml += indent(--indentLevel) + "</" + tagStack.top() + ">\n";
        tagStack.pop();
    }

    // Write prettified HTML back to file
    ofstream outputFile("index.html");
    if (!outputFile.is_open()) {
        cerr << "Error: Could not write to index.html\n";
        return;
    }
    outputFile << formattedHtml;
    outputFile.close();

    cout << "HTML has been prettified and missing tags have been closed successfully!\n";
}

int main() {
    title("My Webpage", "favicon.ico");
    addFont("https://fonts.googleapis.com/css2?family=Roboto:wght@300&display=swap");
    head("Welcome to My Webpage", "h1", { {"color", "blue"}, {"text-align", "center"} });

    Image img("example.jpg", { {"alt", "Example Image"}, {"width", "300px"} });
    img.show();
    img.css({ {"border-radius", "10px"}, {"box-shadow", "2px 2px 10px gray"} });
    
    Table table;
    table.get_table("test.csv", {{"class", "data"}});
    table.css({{"border-collapse", "collapse"}, {"width", "50%"}, {"border", "1px solid black"}});

    Tag div("div", { {"class", "container"}, {"id", "main"} });
    Tag p("p", {}, "Hello, World!");
    CmTag section("section", { {"class", "wrapper"}, {"style", "color: white; background-color: purple"} });
    section.enter();
    div.render();
    p.render();
    section.exit();

    try {
        Bullets b(true, {"Item 1", "Item 2", "Item 3"}, {{"class", "bullet-list"}, {"id", "my-list"}});
        b.enter();
        b.exit();
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    autoPrettify();
    return 0;
}
