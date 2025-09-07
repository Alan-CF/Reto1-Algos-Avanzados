#include <iostream>
#include <string>
using namespace std;

bool isSubsecuence(const string &str, const string &pattern) {
    for (size_t i = 0; i < str.size(); i++) {
        if (str.substr(i, pattern.size()) == pattern) {
            return true;
        }
    }
    return false;
}

