#include <iostream>
#include <string>
using namespace std;

int subsecuenceIdx(const string &str, const string &pattern) {
    for (int i = 0; i + pattern.size() <= str.size(); i++) {
        if (str.substr(i, pattern.size()) == pattern) {
            return i;
        }
    }
    return -1;
}
