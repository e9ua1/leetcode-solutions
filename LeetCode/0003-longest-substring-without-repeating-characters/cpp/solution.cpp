#include<bits/stdc++.h>

using namespace std;

int n, l, ans;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        l = ans =0;
        n = s.size();
        vector<int> cnt(128, 0);

        for (int r = 0; r < n; ++r) {
            char curChar = s[r];
            cnt[curChar]++;

            while (cnt[curChar] > 1) cnt[s[l++]]--;

            ans = max(ans, r - l + 1);
        }

        return ans;
    }
};
