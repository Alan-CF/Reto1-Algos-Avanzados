#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "subsequence.h" //parte 1
#include "palindrome.h" //parte 2
#include "lcs.h" //parte 3
#include "huffman.h" //parte 4

using namespace std;

// Lectura: conserva solo [0-9A-F] del archivo (en cwd)
static inline string readHexFile(const string& filename){
    ifstream in(filename);
    string s, line;
    if(!in) return s;
    while(getline(in, line)){
        for(char c: line){
            if(c>='0' && c<='9') s.push_back(c);
            else if(c>='A' && c<='F') s.push_back(c);
        }
    }
    return s;
}

// Función para encontrar el substring común más largo entre dos transmisiones
void findLCS(const string& t1, const string& t2) {
    // Llamada a la función de lcs.h para encontrar el LCS
    LCSAns result = longestCommonSubstringPosInS1(t1, t2);

    // Mostrar la posición inicial y la longitud del LCS
    cout << "Longest Common Substring found in transmission1 at position: "
         << result.l1 << " with length: " << (result.r1 - result.l1) << endl;
}


int main()
{
    const array<string, 3> mcodeNames = {"txts/mcode1.txt", "txts/mcode2.txt", "txts/mcode3.txt"};
    const array<string, 2> transNames = {"txts/transmission1.txt", "txts/transmission2.txt"};

    array<string, 3> mCodes;
    array<string, 2> transmissions;

    for (size_t i = 0; i < mCodes.size(); ++i) {
        mCodes[i] = readHexFile(mcodeNames[i]);
    }
    for (size_t i = 0; i < transmissions.size(); ++i) {
        transmissions[i] = readHexFile(transNames[i]);
    }

    const string& t1 = transmissions[0];
    const string& t2 = transmissions[1];
    const string& m1 = mCodes[0];
    const string& m2 = mCodes[1];
    const string& m3 = mCodes[2];

    // ---------- Parte 1: Subsequence check --------
    for (size_t i = 0; i < transmissions.size(); i++) {
        for (size_t j = 0; j < mCodes.size(); j++) {
            if (const int idx = subsecuenceIdx(transmissions[i], mCodes[j]); idx != -1) {
                cout << "Found malicious code " << mCodes[j] << " in " << transNames[i] << " at index: " << idx << "\n";
            } else {
                cout << "Malicious code " << mCodes[j] << " not found in " << transNames[i] << "\n";
            }
        }
    }
     // -------- Parte 2: Manacher --------
    {
        auto a = longestPalindrome1Based(t1);
        auto b = longestPalindrome1Based(t2);
        cout << a.l1 << " " << a.r1 << "\n";
        cout << b.l1 << " " << b.r1 << "\n";
    }

    // -------- Parte 3: SA + LCP --------
    cout << "---------- Parte 3: Longest Common Substring --------" << endl;
    findLCS(t1, t2);


    // -------- Parte 4: Huffman --------

    for (size_t i = 0; i < transmissions.size(); i++) {
        HuffmanCoding huffman;
        huffman.buildFromText(transmissions[i]);
        
        for (size_t j = 0; j < mCodes.size(); j++) {
            int mcodeLength = huffman.getCompressedSize(mCodes[j]);
            double averageLength = huffman.getAverageEncodingLength();
            
            // Threshold: if mcode encoding is more than 2x the average, it's suspicious
            double threshold = 2.0;
            bool suspicious = mcodeLength > threshold * averageLength;
            
            if (suspicious) {
                cout << "sospechoso " << mcodeLength << "\n";
            } else {
                cout << "no-sospechoso " << mcodeLength << "\n";
            }
        }
    }

    return 0;
}