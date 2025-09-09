#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct LCSAns { long long l1, r1; };

inline vector<int> build_sa(const string& s){
    int n = (int)s.size();
    vector<int> sa(n), rnk(n), tmp(n);
    iota(sa.begin(), sa.end(), 0);
    for(int i=0;i<n;++i) rnk[i] = (unsigned char)s[i];

    for(int k=1;k<n;k<<=1){
        auto cmp = [&](int a,int b){
            if(rnk[a]!=rnk[b]) return rnk[a]<rnk[b];
            int ra=(a+k<n)? rnk[a+k]:-1;
            int rb=(b+k<n)? rnk[b+k]:-1;
            return ra<rb;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for(int i=1;i<n;++i)
            tmp[sa[i]] = tmp[sa[i-1]] + (cmp(sa[i-1], sa[i])?1:0);
        rnk.swap(tmp);
        if(rnk[sa.back()]==n-1) break;
    }
    return sa;
}

inline vector<int> build_lcp(const string& s, const vector<int>& sa){
    int n=(int)s.size();
    vector<int> rank(n), lcp(n);
    for(int i=0;i<n;++i) rank[sa[i]] = i;
    int h=0;
    for(int i=0;i<n;++i){
        int r=rank[i];
        if(r==0){ h=0; continue; }
        int j=sa[r-1];
        while(i+h<n && j+h<n && s[i+h]==s[j+h]) ++h;
        lcp[r]=h;
        if(h) --h;
    }
    return lcp;
}


inline LCSAns longestCommonSubstringPosInS1(const string& s1, const string& s2){
    if(s1.empty() || s2.empty()) return {1,0};
    const char SEP = '#'; 
    string s = s1 + SEP + s2;
    int n1 = (int)s1.size(), n = (int)s.size();

    auto sa  = build_sa(s);
    auto lcp = build_lcp(s, sa);

    int best = 0, bestStartInS1 = -1;
    for(int i=1;i<n;++i){
        int a = sa[i-1], b = sa[i];
        bool ina = (a < n1);
        bool inb = (b < n1);
        if(ina != inb){
            int cand = lcp[i];
            if(cand > best){
                best = cand;
                bestStartInS1 = ina ? a : b;
            }
        }
    }
    if(best==0) return {1,0};
    return { (long long)bestStartInS1 + 1, (long long)bestStartInS1 + best };
}
