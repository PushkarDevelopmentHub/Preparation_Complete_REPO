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


// Leetcode 1975 -- Maximum Matrix Sum
//Approach - Check Odd or Even count of -ves
//T.C : O(row*col)
//S.C : O(1)
class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        long long sum = 0;
        int countNegatives = 0; 
        int smallestAbsoluteValue = INT_MAX;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                sum += abs(matrix[i][j]);

                countNegatives += matrix[i][j] < 0 ? 1 : 0;

                smallestAbsoluteValue = min(smallestAbsoluteValue, abs(matrix[i][j]));

            }
        }

        if(countNegatives%2 == 0) {
            return sum;
        }

        return sum - 2*smallestAbsoluteValue;
    }
};


// Leetcode 1161 -- Maximum Level Sum of a Binary Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        int maxsum = INT_MIN;
        int resultlevel  = 0;
        queue<TreeNode*> que;
        que.push(root);
        int currlevel = 1;
        while(!que.empty()){
            int n = que.size();
            int sum =0;
            while(n--){
                TreeNode* temp = que.front();
                que.pop();
                sum += temp->val;
                if(temp->left) {
                    que.push(temp->left);
                }
                if(temp->right) {
                    que.push(temp->right);
                }
            }
            if(sum> maxsum){
                maxsum = sum;
                resultlevel = currlevel;
            }
            currlevel++;
        }
        return resultlevel;
    }
};


// Leetcode 1382 -- Maximum Product of Splitted Binary Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
//T.C : O(n)
//S.C : O(n) if we consider recursion stack space, else O(1)
class Solution {
public:
    
    long M = 1e9+7;
    long totalSum = 0, maxP = 0;
    
    int findTotalSum(TreeNode* root) {
        if(!root)
            return 0;
        
        int leftSubtreeSum  = findTotalSum(root->left);
        int rightSubtreeSum = findTotalSum(root->right);
        int sum             = root->val + leftSubtreeSum + rightSubtreeSum;
        
        maxP = max(maxP, (totalSum - sum) * sum);
        
        return sum;
    }
    
    int maxProduct(TreeNode* root) {
        if(!root)
            return 0;
        
        maxP = 0;
        
        totalSum = findTotalSum(root);
        
        
        findTotalSum(root);
        
        return maxP%M;
    }
};


// Leetcode 1458 -- Max Dot Product of Two Subsequences
//Approach-1 (Using concept of LCS - same code)
//T.C : O(m*n)
//S.C : O(m*n)
class Solution {
public:
    int m, n;
    int t[501][501];
    
    int solve(vector<int>& nums1, vector<int>& nums2, int i, int j) {
        if(i == m || j == n)
            return -100000000; //send a large negative number. Don't send 0 because we can have -ve product as well. For example : {-1, -1}, {1, 1}, output should be -1.
        
        if(t[i][j] != -1e9)
            return t[i][j];
        
        int val = nums1[i] * nums2[j];
        
        int take_i_j = solve(nums1, nums2, i+1, j+1) + val;
        
        int take_i = solve(nums1, nums2, i, j+1);
        int take_j = solve(nums1, nums2, i+1, j);
        
        
        return t[i][j] = max({val, take_i_j, take_i, take_j});
        
        
    }
    
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        m = nums1.size();
        n = nums2.size();
        
        for(int i = 0; i<501; i++) {
            for(int j = 0; j < 501; j++) {
                t[i][j] = -1e9;
            }
        }
        
        return solve(nums1, nums2, 0, 0);
    }
};

//Leetcode 865 -- Smallest Subtree with all the Deepest Nodes
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        if (!root) return nullptr;

        unordered_map<TreeNode*, TreeNode*> parent;
        queue<TreeNode*> q;
        q.push(root);
        parent[root] = nullptr;

        vector<TreeNode*> lastLevel;

        // BFS traversal
        while (!q.empty()) {
            int size = q.size();
            lastLevel.clear();

            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                lastLevel.push_back(node);

                if (node->left) {
                    parent[node->left] = node;
                    q.push(node->left);
                }
                if (node->right) {
                    parent[node->right] = node;
                    q.push(node->right);
                }
            }
        }

        unordered_set<TreeNode*> deepest(lastLevel.begin(), lastLevel.end());

        // Move upward until one node remains
        while (deepest.size() > 1) {
            unordered_set<TreeNode*> next;
            for (auto node : deepest) {
                next.insert(parent[node]);
            }
            deepest = next;
        }

        return *deepest.begin();
    }
};


// Leetcode 712 -- Minimum ASCII Delete Sum for Two Strings
//Approach-1 (Using Recursion + Memo (Top Down)) - O(m*n)
//T.C : O(m*n)
//S.C : O(m*n)
class Solution {
public:
    int m, n;
    
    int t[1001][1001];
    
    int solve(string &s1, string &s2, int i, int j) {
        if(i >= m && j >= n)
            return 0;
        
        if(t[i][j] != -1)
            return t[i][j];
        
        if(i >= m) {
            return t[i][j] = s2[j] + solve(s1, s2, i, j+1);
        } else if(j >= n) {
            return t[i][j] = s1[i] + solve(s1, s2, i+1, j);
        }
        
        if(s1[i] == s2[j])
            return t[i][j] = solve(s1, s2, i+1, j+1);
        
        int take_s1_i = s1[i] + solve(s1, s2, i+1, j);
        int take_s2_j = s2[j] + solve(s1, s2, i, j+1);
        
        return t[i][j] = min(take_s1_i, take_s2_j);
    }
    
    int minimumDeleteSum(string s1, string s2) {
        m = s1.length();
        n = s2.length();
        
        memset(t, -1, sizeof(t));
        
        return solve(s1, s2, 0, 0);
    }
};

// Leetcode 85 -- Maximal Rectangle
class Solution {
public:
    vector<int> NSR(vector<int>& heights) {
        stack<int> st;
        int n = heights.size();
        int pseudo_index = n;
        vector<int> right(n);
        for(int i = n-1; i>=0; i--) {
            if(st.empty()) {
                right[i] = pseudo_index;
            } else {
                while(!st.empty() && heights[st.top()] >= heights[i])
                    st.pop();
                if(st.empty())
                    right[i] = pseudo_index;
                else
                    right[i] = st.top();
            }
            st.push(i);
        }
        return right;
    }
    vector<int> NSL(vector<int>& heights) {
        stack<int> st;
        int n = heights.size();
        int pseudo_index = -1;
        vector<int> left(n);
        for(int i = 0; i<n; i++) {
            if(st.empty()) {
                left[i] = pseudo_index;
            } else {
                while(!st.empty() && heights[st.top()] >= heights[i])
                    st.pop();
                if(st.empty())
                    left[i] = pseudo_index;
                else
                    left[i] = st.top();
            }
            st.push(i);
        }
        return left;
    }
    
    int MAH(vector<int>& heights) {
        int n = heights.size();
        vector<int> right = NSR(heights);
        vector<int> left  = NSL(heights);
        vector<int> width(n);
        for(int i = 0; i<n; i++)
            width[i] = right[i]-left[i]-1;
        int max_area = 0;
        
        for(int i = 0; i<n; i++) {
            int a =  width[i]*heights[i];
            if(max_area < a)
                max_area = a; 
        }
        return max_area;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.size() == 0)
            return 0;
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> height(m);
        for(int i = 0; i<m; i++) {
            height[i] = (matrix[0][i]=='1')?1:0;
        }
        int maxA = MAH(height);
        for(int i = 1; i<n; i++) {
            for(int j = 0; j<m; j++) {
                if(matrix[i][j] == '0')
                    height[j] = 0;
                else
                    height[j] += 1;
            }
            maxA = max(maxA, MAH(height));
        }
        return maxA;
    }
};