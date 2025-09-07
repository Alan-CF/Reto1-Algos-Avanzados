#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "subsequence.h"

using namespace std;

string readFile(const string& filePath)
{
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "File could not be opened.\n";
    }
    string content;
    getline(file, content);

    return content;
}

int main()
{
    string mCodePaths[3] = {
        "../txts/mcode1.txt",
        "../txts/mcode2.txt",
        "../txts/mcode3.txt"
    };

    string transmissionPaths[2] = {
        "../txts/transmission1.txt",
        "../txts/transmission2.txt"
    };

    array<string, 3> mCodes;
    array<string, 2> transmissions;

    for (size_t i = 0; i < mCodes.size(); i++) {
        mCodes[i] = readFile(mCodePaths[i]);
    }
    for (size_t i = 0; i < transmissions.size(); i++) {
        transmissions[i] = readFile(transmissionPaths[i]);
    }

    // Subsequence check
    for (size_t i = 0; i < transmissions.size(); i++) {
        for (size_t j = 0; j < mCodes.size(); j++) {
            if (isSubsecuence(transmissions[i], mCodes[j])) {
                cout << "MCode found: " << mCodes[j] << " in " << transmissionPaths[i] << "\n";
            } else {
                cout << "MCode not found: " << mCodes[j] << " in " << transmissionPaths[i] << "\n";
            }
        }
    }

    return 0;
}