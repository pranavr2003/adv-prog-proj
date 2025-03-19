#include "bullets_and_lists.h"

Bullets::Bullets(bool ul, vector<string> points, map<string, string> kwargs)
    : ul(ul), points(points), kwargs(kwargs) {}

void Bullets::enter() {
    html.str("");
    html << "\n" << (ul ? "<ul" : "<ol");
    for (auto& pair : kwargs) {
        string key = pair.first, value = pair.second;
        replace(key.begin(), key.end(), '_', '-');
        key.erase(remove(key.begin(), key.end(), '_'), key.end());
        html << " " << key << "=\"" << value << "\"";
    }
    html << ">\n";
    for (const string& point : points) {
        html << "<li>" << point << "</li>\n";
    }
}

void Bullets::exit() {
    html << (ul ? "</ul>\n" : "</ol>\n");
    writeToFile();
}

void Bullets::writeToFile() {
    ofstream file("index.html", ios::app);
    if (file) {
        file << html.str();
    } else {
        cerr << "Error opening file" << endl;
    }
}

// int main() {
    // try {
    //     Bullets b(true, {"Item 1", "Item 2", "Item 3"}, {{"class", "bullet-list"}, {"id", "my-list"}});
    //     b.enter();
    //     b.exit();
    // } catch (const exception& e) {
    //     cerr << "Exception: " << e.what() << endl;
    // }
//     return 0;
// }