class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
            return a.length() < b.length();
        });

        string longest = "";
        string check = strs[0];
        for (int i = 0; i < check.length(); i++) {
            bool flag = false;
            for (auto j : strs) {
                if (j[i] == check[i]) {
                    flag = true;
                } else {
                    flag = false;
                    break;
                }
            }

            if (flag == true) {
                longest += check[i];
            }

            else {
                break;
            }
        }
        return longest;
    }
};