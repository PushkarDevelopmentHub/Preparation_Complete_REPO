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

// 3 Question -- 3Sum
class Solution {
public:
vector<vector<int>> ans;
    void   twoSum(vector<int>& nums, int i, int j, int t){
        while(i <j){
            int sum= nums[i]+nums[j];
            if(sum < t) i++;
            else if(sum > t) j--;
            else {
                while(i<j && nums[i] == nums[i+1]) i++;
                while(i< j && nums[j] == nums[j-1]) j--;
                ans.push_back({-t, nums[i], nums[j]});
                i++; j--;
            }
        }
        
    }
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        if(n <3) return {} ;
        sort(nums.begin(), end(nums));
        
        for(int i= 0; i<n; i++){
            if(i> 0 && nums[i] == nums[i-1]){
                continue;
            }
            int k= nums[i];
            int target = -k;
            twoSum(nums, i+1, n-1, target);
        }
        return  ans;
    }
};


// 4 Question -- Trapping Rain Water | without stack
class Solution {
public:
    vector<int> getl(vector<int>& h, int &n){
        vector<int> l(n);
        l[0] = h[0];
        for(int i=1; i<n; i++){
            l[i] = max(l[i-1], h[i]);
        }
        return l;
    }
    vector<int> getr(vector<int>& h, int &n){
        vector<int> r(n);
        r[n-1] = h[n-1];
        for(int i=n-2; i>=0; i--){
            r[i] = max(r[i+1], h[i]);
        }
        return r;
    }    
    int trap(vector<int>& height) {
        int n = height.size();
        int sum =0;
        vector<int> left  = getl(height, n);
        vector<int> right = getr(height, n);
        for(int i=0; i<n; i++){
           int hig= min(left[i], right[i]) - height[i];
            sum += hig;
        }
        return sum;
    }
};


// 5 Question -- 3Sum Closest
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
     int n =  nums.size();
     int cs = 100000;
     sort(begin(nums), end(nums));
     for(int i=0; i<=n-3; i++){
        int k = i+1;
        int j = n-1;
        while(k<j){
            int s = nums[i]+ nums[k]+nums[j];
            if(abs(target - s) < abs(target-cs)){
                cs = s;
            }
            if(s< target) k++;
            else j--;
        }
     }
     return cs;
    }
};