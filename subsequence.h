#pragma once
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


#ifndef SUBSEQUENCE_H
#define SUBSEQUENCE_H

#endif //SUBSEQUENCE_H
