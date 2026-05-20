class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int high = nums.size();
        int low = 0;
        int mid = -1;
        bool flag = false;

        if(target > nums[nums.size()-1]) {
            return nums.size();
        }

        if(target < nums[0]) {
            return 0;
        }

        while(low <= high) {
            mid = low + (high-low)/2;
            if(nums[mid] > target) {
                high = mid-1;
            }

            else if(nums[mid] < target) {
                low = mid+1;
            }

            else{
                return mid;
            }
        }

       return low;
    }
};