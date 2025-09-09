#pragma once
#include <string>
#include <vector>

using namespace std;
// ---------------- Parte 2: Palíndromo más largo (Manacher) ----------------

struct PalAns { long long l1, r1; }; // 1-based

inline PalAns longestPalindrome1Based(const string& s){
    int n=(int)s.size();
    if(n==0) return {1,0};
    string t; t.reserve(2*n+3);
    t.push_back('^'); t.push_back('#');
    for(char c: s){ t.push_back(c); t.push_back('#'); }
    t.push_back('$');

    int m=(int)t.size();
    vector<int> P(m,0);
    int C=0,R=0,best=0,center=0;
    for(int i=1;i<m-1;++i){
        int mir=2*C-i;
        if(i<R) P[i]=min(R-i, P[mir]);
        while(t[i+1+P[i]]==t[i-1-P[i]]) ++P[i];
        if(i+P[i]>R){ C=i; R=i+P[i]; }
        if(P[i]>best){ best=P[i]; center=i; }
    }
    int start0=(center-best)/2;
    int end0=start0+best-1;
    return { (long long)start0+1, (long long)end0+1 };
}
