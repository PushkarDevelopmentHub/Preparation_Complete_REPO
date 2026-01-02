// Leetcode 66 -- Plus One | Constraint Analysis
// Approach (Simple follow Math Addition Principles) //T.C : O(n) //S.C : O(1)
class Solution
{
public:
  vector<int> plusOne(vector<int> &digits)
  {
    int n = digits.size();

    int i = n - 1; // Start from LSB like usual math addition

    while (i >= 0)
    {
      if (digits[i] < 9)
      {
        digits[i] += 1;
        return digits;
      }

      // else we did get 9
      digits[i] = 0; // 9+1 = 10
      i--;
    }

    digits.insert(begin(digits), 1); // 1 is the carry forwarded till the end

    return digits;
  }
};




//++++++++++++++++++++++
//Leetcode 961-Repeated Element in Size 2N Array
//Approach-1 (Using Hashset)
//T.C : O(n)
//S.C : O(n)
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        unordered_set<int> st;
        
        for (int &num : nums) {
            if(st.count(num))
                return num;
            
            st.insert(num);
        }
        
        return -1;
    }
};

//Approach-2 (Using 10^4 Size array ~ Constant Space)
//T.C : O(n)
//S.C : O(1)
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {    
        vector<int> freq(10001, 0);
        
        for (int &num : nums) {
            freq[num]++;
            if (freq[num] > 1) //all other elements appear exactly once
                return num;
        }
        
        return -1;
    }
};



//Approach-3 (Without using any extra variable to store space - True Constant Space)
//T.C : O(n)
//S.C : O(1)
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        int n = nums.size();
        
        for(int i = 2; i<n; i++) {
            if(nums[i] == nums[i-1] || nums[i] == nums[i-2])
                return nums[i];
        }
        
        return nums[n-1]; //or, nums[0]
    }
};
