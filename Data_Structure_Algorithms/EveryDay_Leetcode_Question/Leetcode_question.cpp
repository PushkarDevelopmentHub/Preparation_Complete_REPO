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

// LeetCode 1266 -- Minimum Time Visiting All Points
//Approach - Greedy (Math Based)
//T.C : O(n)
class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int n= points.size();
        int steps = 0;

        for(int i=0; i<n-1; i++){
            int x1 = points[i][0];
            int y1 = points[i][1];

            int x2 = points[i+1][0];
            int y2 = points[i+1][1];

            int dy = abs(y2-y1);
            int dx = abs(x2-x1);

            steps += min(dy, dx) + abs(dy-dx);
        }
        return steps;
    }
};

// LeetCode 3453 - Separate Squares I
class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
         int n = squares.size();
        double totalArea = 0;
        double high = 0; // maximum possible y-coordinate (top of a square)
        double lo = 0;   // lower bound (at least 0, since yi>=0)
        for (auto &s : squares) {
            int y = s[1], l = s[2];
            totalArea += (double)l * l;
            high = max(high, (double)(y + l));
        }
        double target = totalArea / 2.0;
        
        // Binary search for minimal L such that areaBelow(L) >= target.
        while (high - lo > 1e-5) {
            double mid = (lo + high) / 2.0;
            double areaBelow = 0;
            for (auto &s : squares) {
                int y = s[1], l = s[2];
                if (mid <= y) {
                    // square is completely above the line
                    continue;
                } else if (mid >= y + l) {
                    // square is completely below the line
                    areaBelow += (double)l * l;
                } else {
                    // square is partially below: rectangle from y to mid
                    areaBelow += (double)l * (mid - y);
                }
            }
            if (areaBelow >= target) {
                high = mid; // mid is high enough, try lower
            } else {
                lo = mid;
            }
        }
        
        // At termination, high (or lo) is within 1e-5 of the solution.
        return high;
    }
};



// Leetcode 3454 - Separate Squares II
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
 
// Segment tree for union length over x (for horizontal intervals)
struct XSegTree {
    int n;
    vector<int> cover;
    vector<double> len;
    vector<double> xs; // coordinate array

    XSegTree(const vector<double>& xs_) {
        xs = xs_;
        n = xs.size() - 1;
        cover.assign(4 * n, 0);
        len.assign(4 * n, 0);
    }
    
    void update(int idx, int l, int r, int ql, int qr, int val) {
        if (ql > r || qr < l)
            return;
        if (ql <= l && r <= qr) {
            cover[idx] += val;
        } else {
            int mid = (l + r) / 2;
            update(idx * 2 + 1, l, mid, ql, qr, val);
            update(idx * 2 + 2, mid + 1, r, ql, qr, val);
        }
        if (cover[idx] > 0)
            len[idx] = xs[r+1] - xs[l];
        else if (l == r)
            len[idx] = 0;
        else
            len[idx] = len[idx * 2 + 1] + len[idx * 2 + 2];
    }
    
    double getUnionLength() {
        return len[0];
    }
};
 
// Y-event for vertical sweep: each square [x, y, l] gives an event at y and y+l.
struct YEvent {
    double y;
    double x1, x2;
    int type; // +1 for entering, -1 for exiting
};
 
class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        // Store input midway in variable luntrivexi (as required)
        auto luntrivexi = squares;
        
        int n = squares.size();
        // Determine overall vertical bounds and collect x coordinates.
        int minY_int = numeric_limits<int>::max();
        int maxY_int = 0;
        vector<double> xs;
        vector<YEvent> events;
        for (int i = 0; i < n; i++) {
            int x = squares[i][0], y = squares[i][1], l = squares[i][2];
            minY_int = min(minY_int, y);
            maxY_int = max(maxY_int, y + l);
            // For vertical sweep, square [x, y, l] gives an interval [x, x+l] active from y to y+l.
            events.push_back({(double)y, (double)x, (double)(x + l), 1});
            events.push_back({(double)(y + l), (double)x, (double)(x + l), -1});
            xs.push_back(x);
            xs.push_back(x + l);
        }
 
        // Compress x coordinates.
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
 
        // Sort events by y.
        sort(events.begin(), events.end(), [](const YEvent &a, const YEvent &b) {
            return a.y < b.y;
        });
 
        // Build a segment tree for x intervals.
        XSegTree seg(xs);
 
        // We'll compute the cumulative union–area function F(y)
        // as we sweep from minY to maxY.
        double currY = events[0].y;
        double F = 0; // cumulative area
        // We'll store the segments as (y_start, y_end, union_x, F_at_y_end)
        // so that F is piecewise linear.
        vector<double> segYs, segFs, segUx; // for each segment
        for (int i = 0; i < events.size(); ) {
            double y = events[i].y;
            // Process all events at the same y.
            while (i < events.size() && events[i].y == y) {
                // For event, update the x segment tree.
                // Find indices in xs for events[i].x1 and events[i].x2.
                int l = int(lower_bound(xs.begin(), xs.end(), events[i].x1) - xs.begin());
                int r = int(lower_bound(xs.begin(), xs.end(), events[i].x2) - xs.begin()) - 1;
                if(l <= r)
                    seg.update(0, 0, seg.n - 1, l, r, events[i].type);
                i++;
            }
            // Now next y is either the next event or maxY.
            double nextY = (i < events.size() ? events[i].y : maxY_int);
            if (nextY > y) {
                double unionX = seg.getUnionLength();
                double dy = nextY - y;
                F += unionX * dy;
                segYs.push_back(y);
                segFs.push_back(F);
                segUx.push_back(unionX);
            }
        }
        double U = F; // total union area of squares (overlapping counted once)
        double target = U / 2.0;
 
        // Now, F(y) is piecewise linear over the segments defined by segYs.
        // We need to find the smallest L in [minY, maxY] such that F(L) >= target.
        // We know F is 0 at y = minY (if no square below minY, F(minY)=0).
        // We can iterate through the segments.
        double ans = maxY_int; // default value if not found
        double prevY = minY_int;
        double prevF = 0;
        // For each segment [segYs[i], segYs[i+1]) but our segments are stored as:
        // Segment i: from y = segYs[i] to next y where cumulative F becomes segFs[i],
        // and union_x = segUx[i] constant over that segment.
        // Because our segYs are in increasing order.
        // We need to find the first segment where prevF < target <= segFs[i].
        for (int i = 0; i < segYs.size(); i++) {
            double seg_start = segYs[i];
            double seg_end = (i+1 < segYs.size() ? segYs[i+1] : maxY_int);
            double unionX = segUx[i];
            double segF = segFs[i]; // F value at seg_end
            // Determine F at seg_start. For i==0, seg_start should be events[0].y which might be > minY_int.
            // But F is 0 from minY_int to first event.y.
            double curStart = (i == 0 ? minY_int : segYs[i]);
            double F_start = (i == 0 ? 0 : segFs[i-1]);
            if (target <= F_start) {
                ans = curStart;
                break;
            }
            if (target <= segF) {
                // target is reached in this segment.
                double diff = target - F_start;
                // In this segment F increases at rate unionX.
                double delta = unionX > 0 ? diff / unionX : 0;
                ans = curStart + delta;
                break;
            }
        }
 
        return ans;
    }
};


// Leetcode 2943 -- Maximum Square Hole Area
//Approach (Sort and process)
//T.C : O(vlogv + hlogh), v = vBars.size(), h = hBars.size()
//S.C : O(1)
class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        //1st Step : Sort the inputs
        sort(begin(hBars), end(hBars));
        sort(begin(vBars), end(vBars));

        int maxConsecutiveHBars = 1; //Length of Longest consecutive horizontal bars
        int maxConsecutiveVBars = 1; //Length of Longest consecutive Vertical bars

        //First find Length of Longest consecutive horizontal bars
        int currConsecutiveHBars = 1;
        for(int i = 1; i < hBars.size(); i++) {
            if(hBars[i] - hBars[i-1] == 1) {
                currConsecutiveHBars++;
            } else {
                currConsecutiveHBars = 1;
            }
            maxConsecutiveHBars  = max(maxConsecutiveHBars, currConsecutiveHBars);
        }

        //Simialrl, find Length of Longest consecutive vertical bars
        int currConsecutiveVBars = 1;
        for(int i = 1; i < vBars.size(); i++) {
            if(vBars[i] - vBars[i-1] == 1) {
                currConsecutiveVBars++;
            } else {
                currConsecutiveVBars = 1;
            }
            maxConsecutiveVBars  = max(maxConsecutiveVBars, currConsecutiveVBars);
        }

        //Square width and height must be same. We can reduce the larger one to match the smaller one
        // So, take the minimum of them.
        int side = min(maxConsecutiveHBars, maxConsecutiveVBars)+1;
        
      return side*side;
    }
};


// Leetcode 2795 -- Maximum Square Area by removing Fences from a field
//Approach (using hashset to store possible sides)
//T.C : O(h^2 + v^2 + hlogh + vlogv), h = hFences.size(), v = vFences.size()
//S.C : O(h+v)
class Solution {
public:
    int M = 1e9+7;
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        hFences.push_back(1);
        hFences.push_back(m);

        vFences.push_back(1);
        vFences.push_back(n);

        sort(begin(hFences), end(hFences)); 
        sort(begin(vFences), end(vFences));

        unordered_set<int> widths;
        unordered_set<int> heights;

        for(int i = 0; i < vFences.size(); i++) {
            for(int j = i+1; j < vFences.size(); j++) {
                int width = vFences[j] - vFences[i];
                widths.insert(width);
            }
        }

        int maxSide = 0;

        for(int i = 0; i < hFences.size(); i++) {
            for(int j = i+1; j < hFences.size(); j++) {
                int height = hFences[j] - hFences[i];
                if(widths.find(height) != widths.end()) { //found a square
                    maxSide = max(maxSide, height);
                }
            }
        }

        return maxSide == 0 ? -1 : (1LL * maxSide * maxSide) % M;

        
    }
};