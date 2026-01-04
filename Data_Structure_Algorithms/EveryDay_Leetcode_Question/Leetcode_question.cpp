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


// Leetcode 1931 -- Painting a Grid With Three Different Colors
//Approach (Recursion + Memoization)
//T.C : O(n * S * S * m), where S = total states i.e. 3 * 2^m-1
//S.C : O((n * S) + (S * m)) where n * S is because of memoization array t, and S * m is for storing columnStates
class Solution {
public:
    vector<vector<int>> t;
    vector<string> columnStates;
    const int MOD = 1e9 + 7;

    // Recursively generate all valid column colorings of height 'rows'
    // such that no two vertically adjacent cells have the same color
    void generateColumnStates(string currentColumn, int rowsRemaining, char prevColor) {
        if (rowsRemaining == 0) {
            columnStates.push_back(currentColumn);
            return;
        }

        // Colors: 'R' = Red, 'G' = Green, 'B' = Blue
        for (char color : {'R', 'G', 'B'}) {
            if (color == prevColor) 
                continue;  // adjacent vertical cells must be different

            generateColumnStates(currentColumn + color, rowsRemaining - 1, color);
        }
    }

    int solve(int remainingCols, int prevColumnIdx, int m) {
        if (remainingCols == 0) 
            return 1;
        if (t[remainingCols][prevColumnIdx] != -1) 
            return t[remainingCols][prevColumnIdx];

        int totalWays = 0;
        string prevColumn = columnStates[prevColumnIdx];

        for (int nextColumnIdx = 0; nextColumnIdx < columnStates.size(); nextColumnIdx++) {
            string nextColumn = columnStates[nextColumnIdx];
            bool valid = true;

            // Check horizontal adjacency (no adjacent same color in same row)
            for (int r = 0; r < m; r++) {
                if (prevColumn[r] == nextColumn[r]) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                totalWays = (totalWays + solve(remainingCols - 1, nextColumnIdx, m)) % MOD;
            }
        }

        return t[remainingCols][prevColumnIdx] = totalWays;
    }

    int colorTheGrid(int m, int n) {
        columnStates.clear();
        generateColumnStates("", m, '#');  // '#' indicates no previous color

        int numColumnPatterns = columnStates.size();
        t.assign(n, vector<int>(numColumnPatterns, -1));

        int result = 0;
        for (int i = 0; i < numColumnPatterns; i++) {
            result = (result + solve(n - 1, i, m)) % MOD;
        }

        return result;
    }
};

// Leetcode - 1411. Number of Ways to Paint N × 3 Grid 3jan
//Approach (Recursion + Memoization : DP On Grids) - If you want, I can make a separate video on Bottom Up. Let me know in the comments
//T.C : O(n)
//S.C : O(n)
class Solution {
public:
    int M = 1e9 + 7;
    vector<vector<int>> t;

    //12 possible first rows
    string states[12] = {"RYG", "RGY", "RYR", "RGR", "YRG", "YGR", "YGY", "YRY", "GRY", "GYR", "GRG", "GYG"};

    int solve(int n, int prev) {
        if(n == 0)
            return 1;
        
        if(t[n][prev] != -1)
            return t[n][prev];

        int result = 0;
        string last = states[prev];

        for(int curr = 0; curr < 12; curr++) {
            if(curr == prev)
                continue;
            
            string currPat = states[curr];
            bool conflict = false;
            for(int col = 0; col < 3; col++) {
                if(currPat[col] == last[col]) {
                    conflict = true;
                    break;
                }
            }

            if(!conflict) {
                result = (result + solve(n-1, curr)) % M;
            }
        }

        return t[n][prev] = result;
    }

    int numOfWays(int n) {
        t.resize(n, vector<int>(12, -1)); //T.C : O(n)
        int result = 0;

        for(int i = 0; i < 12; i++) { //chossing 1st row
            //now remaining n-1 rows painting
            result = (result + solve(n-1, i)) % M;
        }

        return result;
    }
};


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


// Leetcode 1390 -- Four Divisors
class Solution {
public:
    int findSumDivisors(int num){
        int divisors = 0;
        int sum =0;
        for(int fact = 1; fact*fact <= num; fact++){
            if(num%fact ==0){
                int other = num/fact;

                if(other == fact){
                    divisors += 1;
                    sum += fact;
                }
                else {
                    divisors += 2;
                    sum+= fact +other;
                }
            }
            if(divisors > 4){
                return 0;
            }
        }
        return divisors == 4 ? sum : 0;
    }
    int sumFourDivisors(vector<int>& nums) {
         int n = nums.size();
         int result =0;
         for(int &num : nums){
            result += findSumDivisors(num);
         }
         return result;
    }
};