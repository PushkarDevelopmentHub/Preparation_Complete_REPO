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

// 6 Question -- Factorial Of Large Numbers
class Solution {
public:
    void multiply(vector<int>& arr, int& size, int multiplier){
        int carry =0;
        for(int i=0; i<size; i++){
            int product = arr[i] * multiplier + carry;
            arr[i] = product % 10;
            carry = product / 10;
        }
        while(carry){
            arr[size] = carry % 10;
            carry = carry / 10;
            size++;
        }
    }

    vector<int> factorial(int N){
        vector<int> arr(10000, 1);
        arr[0] = 1;
        int size = 1;
        for(int multiplier = 2; multiplier<=N; multiplier++){
            multiply(arr, size, multiplier);
        }
            vector<int> res;
            for(int i = size -1; i>=0; i--){
                res.push_back(arr[i]);
            }
        return arr;
    }
};

// 7 Question -- Next Permutation 
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // next_permutation(begin(nums), end(nums));

        //2apporach
        int n = nums.size();
        int gola_index =-1;
        for(int i= n-2; i>=0; i--){
            if(nums[i]< nums[i+1]){
                gola_index = i;
                break;
            }
        }
        if(gola_index != -1){
            for(int i = n-1; i>=gola_index; i--){
                if(nums[i] > nums[gola_index]){
                    swap(nums[i], nums[gola_index]);
                    break;
                }
            }
        }
        reverse(nums.begin() + gola_index +1, nums.end());

    }
};

// 8 Question -- Rotate Image
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i=0; i<n; i++){
            for(int j = i; j<n; j++){
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        for(int i=0; i<n; i++){
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

// 9 Question -- Container With Most Water Leetcode 11
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n= height.size();
        int i=0, j= n-1;
        int maxwater = 0;
        while(i<j){
            int w = j-i;
            int h = min(height[i], height[j]);
            int area = h*w;
            maxwater = max(area, maxwater);
            if(height[i] > height[j]){
                j--;
            }else{
                i++;
            }
        }
        return maxwater;
    }
};


// 10 Question -- Spiral Matrix | Leetcode-54
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(); //row
        int n = matrix[0].size(); //col

        int top = 0, bottom= m-1;
        int left =0, right = n-1;
        int dir =0;
        vector<int> res;
        while(top <= bottom && left <= right){
            if(dir == 0){
                //l to r constant row
                for(int i = left; i<=right; i++){
                    res.push_back(matrix[top][i]);
                }           
                top++;
            }
            if(dir == 1){
                //t to d contant col
                for(int i = top; i<=bottom; i++){
                    res.push_back(matrix[i][right]);
                }
                right--;
            }
            if(dir == 2){
                //t to d contant col
                for(int i = right; i>=left; i--){
                    res.push_back(matrix[bottom][i]);
                }
                bottom--;
            }
            if(dir == 3){
                //t to d contant col
                for(int i = bottom; i>=top; i--){
                    res.push_back(matrix[i][left]);
                }
                left++;
            }
            dir++;
            if(dir == 4){
                dir = 0;
            }
        
        }
        return res;

    }
};

// 11 Question -- Group Anagrams | using sorting Leetcode 49
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();
        vector<vector<string>> res;
        unordered_map<string, vector<string>> mp;
        for(int i=0; i<n; i++){
            string temp = strs[i];
            sort(temp.begin(), temp.end());
            mp[temp].push_back(strs[i]);
        }

        for(auto it : mp){
            res.push_back(it.second);
        }
        return res;
    }
};

//Group Anagrams | without sortingGroup Anagrams | without sorting
class Solution {
public:
string generate(string& word){
    int a[26] = {0};
    for(char &ch : word){
        a[ch - 'a']++;
    }
    string NW = "";
    for(int i=0; i<26; i++){
        int freq = a[i];
        if(freq > 0){
            NW += string(freq, i+'a');
        }
    }
    return NW;
}
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();
        vector<vector<string>> res;
        unordered_map<string, vector<string>> mp;
        for(int i=0; i<n; i++){
            string word = strs[i];
            
            string nw = generate(word);

            mp[nw].push_back(strs[i]);
        }

        for(auto it : mp){
            res.push_back(it.second);
        }
        return res;
    }
};

// 12 Question -- Sort the Matrix Diagonally | Leetcode 1329 | Similar to Leetcode 498
// mp[i-j] approach
class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int m = mat.size(); //row
        int n= mat[0].size(); //col

        unordered_map<int, vector<int>> mp;
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                mp[i-j].push_back(mat[i][j]);
            }
        }

        // sort them
        for(auto &it : mp){
            sort(begin(it.second), end(it.second));
        }

        for(int i=m-1; i>=0; i--){
            for(int j=n-1; j>=0; j--){
                mat[i][j] = mp[i-j].back();
                mp[i-j].pop_back();
            }
        }
    return mat;
    }
};


// 13 Question -- Diagonal Traverse | Leetcode 498 | Similar to Leetcode 1329
// mp[i+j] approach
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
         int m = mat.size(); //row
        int n= mat[0].size(); //col
        vector<int> result;

        map<int, vector<int>> mp;
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                mp[i+ j].push_back(mat[i][j]);
            }
        }

        bool flip = true;
        for(auto &it : mp){
            if(flip){
                reverse(it.second.begin(), it.second.end());
            }
            for(int &num : it.second){
                result.push_back(num);
            }
            flip = !flip;
        }
        return result;
        
    }
};


// 14 Question -- Sort Colors
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
int i=0, j=0, k=n-1;
while(j<=k){
    if(nums[j]==0){
        swap(nums[i], nums[j]);
        i++;
        j++;
    }
    else if(nums[j]==1){
        j++;
    }
    else{
        swap(nums[j], nums[k]);
        k--;
    }
}
    }
}; 


// 15 Question -- Find Original Array From Doubled Array
class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        int n= changed.size();
        if(n%2 != 0){
            return {};
        }
        sort(changed.begin(), end(changed));

        map<int, int> mpp;

        vector<int> res;

        for(auto& num: changed){
            mpp[num]++;
        }

        for(auto& num: changed){
            int twice = 2*num;

            if(mpp[num] == 0) continue; 

            if(mpp.find(twice) == mpp.end() || mpp[twice] == 0){
                return {};
            }
            res.push_back(num);

            mpp[num]--;
            mpp[twice]--;
        }

        return res;
    }
};

// 16 Question -- Sum of Even Numbers After Queries
class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n= nums.size();
        int q= queries.size();

        int sumEven = 0;
        vector<int> res;

        //find sumEven
        for(int &x : nums){
            if(x%2 ==0 ){
                sumEven += x;
            }
        }

            for(int i=0; i<q; i++){
                int val = queries[i][0];
                int idx = queries[i][1];

                if(nums[idx] % 2 == 0){
                    sumEven -= nums[idx];
                }

                nums[idx] += val;

                if(nums[idx] % 2 == 0){
                    sumEven += nums[idx];
                }

                res.push_back(sumEven);
            }

    return res;
    }
};


// Question 18 - Find Pivot Index | Leetcode 724
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int n = nums.size();
        int sum =0;
        for(int &x : nums){
            sum += x;
        }
        int cs = 0;
        for(int i=0; i<n; i++){
            int ls = cs;
            int rs = sum - cs -nums[i];
            if(ls == rs){
                return i;
            }
            cs += nums[i];
        }
        return -1;
    }
};


// Question - 19 Increasing Triplet Subsequence
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
          int n1 = INT_MAX, n2 = INT_MAX, n3;
          for(int i=0; i<n; i++){
            n3 = nums[i];
            if(n3 <= n1){
                n1 = n3;
            }else if(n3 <= n2){
                n2 = n3;
            }else {
               return true; 
            }
          }
          return false;
    }
};

// Question - 20 -- Largest Perimeter Triangle | Leetcode 976
class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), end(nums));

        for(int i= n-3; i>=0; i--){
            if(nums[i]  + nums[i+1] > nums[i+2]){
                return nums[i]  + nums[i+1] + nums[i+2];
            }
        }
        return 0;
    }
};

// Question - 21 -- Contains Duplicate II | Leetcode 219
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();

        map<int, int> mp;
        for(int i=0; i<n; i++){
            if(mp.find(nums[i]) != mp.end() && 
            abs(mp[nums[i]] - i) <= k){
                return true;
            }else{
                mp[nums[i]] = i;
            }
        }
    return false;
    }
};