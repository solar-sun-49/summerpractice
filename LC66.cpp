class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        reverse(digits.begin(),digits.end());
        digits[0]++;
        bool carry = false;
        if(digits[0] >= 10) {
            carry = true;
            digits[0] = digits[0]%10;
        }
    
        for(int i = 1;i<digits.size();i++) {
            if(carry == true) {
                digits[i]++;
                if(digits[i] >= 10) {
                    carry = true;
                    digits[i] = digits[i] % 10;
                }

                else{
                    carry = false;
                }
            }
        }

        if(carry == true) {
            digits.push_back(1);
        }
        reverse(digits.begin(),digits.end());
        return digits;
    }
};