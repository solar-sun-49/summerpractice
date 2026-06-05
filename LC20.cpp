class Solution {
public:
    bool isValid(string s) {
        int n = s.length();
        stack<char> stk;
        bool flag = false;
        if(s[0] != '(' && s[0] != '{' && s[0] != '[') return false;

        for(int i=0;i<n;i++) {
            if(s[i] == '(' || s[i] == '{' || s[i] == '[') {
                stk.push(s[i]);
            }

            else{
                if(stk.size() > 0 && stk.top() == '{' && s[i] == '}') {
                    stk.pop();
                    flag = true;

                }
                else if(stk.size() > 0 && stk.top() == '(' && s[i] == ')') {
                    stk.pop();
                    flag = true;
                }
                else if(stk.size() > 0 && stk.top() == '[' && s[i] == ']') {
                    stk.pop();
                    flag = true;
                }

                else{
                    return false;
                }
            }
        }


        if(stk.size() == 0 && flag == true) {
            return true;
        }

        else{
            return false;
        }
    }
};