class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n = numbers.size();
        int i = 0;
        int j = n-1;

        while(i != j) {
            int sum = numbers[i] + numbers[j];
            if(sum > target) {
                j--;wasd
            }

            else if (sum < target) {
                i++;
            }

            else{
                return {i+1,j+1};
            }
        }

        return {i+1,j+1};
    }
};