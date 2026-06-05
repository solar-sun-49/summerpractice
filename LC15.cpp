class Solution {
public:
    vector<vector<int>> result;
    
    // FIX 2: Passed by reference using '&' to avoid O(N) deep copies
    void twoSum(const vector<int>& nums, int target, int i, int j) {
        while(i < j) {
            if(nums[i] + nums[j] < target) {
                i++;
            }
            else if (nums[i] + nums[j] > target) {
                j--;
            }
            else {
                while(i < j && nums[i] == nums[i+1]) i++;
                while(i < j && nums[j] == nums[j-1]) j--;
                result.push_back({-target, nums[i], nums[j]});
                i++;
                j--;
            }
        }
    }
    
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();

        if(n < 3) {
            return {};
        }
        
        sort(nums.begin(), nums.end());
        result.clear();
        
        for(int i = 0; i <= n - 2; i++) {
            // FIX 1: Swapped conditions to prevent Out-of-Bounds crash on i=0
            if(i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            int n1 = nums[i];
            int target = 0 - n1;
            twoSum(nums, target, i + 1, n - 1);            
        }

        return result;
    }
};