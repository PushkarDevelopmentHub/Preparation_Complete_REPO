// 1 Questions -- Two Sum
class Solution {
public:
   vector<int> twoSum(vector<int>& nums, int t){
    int n = nums.size();
    map<int, int> mp;
      for(int i = 0; i < n; i++){
        int complement = t - nums[i];
        if(mp.find(complement) != mp.end()){
            return {mp[complement], i};
        }
        mp[nums[i]] = i;
      }
      return {};
   }
};

// 2 Question -- Two Sum II - Input Array Is Sorted
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        int i= 0, j= n-1;
        while(i<j){
            int s = nums[i]+nums[j];
            if(s < target) i++;
            else if(s > target) j--;
            else{
                return {i+1, j+1};
            }
        }
        return {-1, -1};
    }
};