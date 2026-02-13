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


// Leetcode 3047 - Find the Largest Area of Square Inside Two Rectangles
//Approach - (Just find all possible intersections and best square side from them)
//T.C : O(n * n)
//S.C : O(1)
class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        int n = bottomLeft.size(); //topRight.size()

        int maxSide = 0;

        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                //Width
                int topRightX   = min(topRight[i][0], topRight[j][0]);
                int bottomLeftX = max(bottomLeft[i][0], bottomLeft[j][0]);

                int width = topRightX - bottomLeftX;

                //Height
                int topRightY   = min(topRight[i][1], topRight[j][1]);
                int bottomLeftY = max(bottomLeft[i][1], bottomLeft[j][1]);

                int height = topRightY - bottomLeftY;

                int side = min(width, height);

                maxSide = max(maxSide, side);
            }
        }

        return 1LL * maxSide*maxSide;
    }
};


// 16 Leetcode 1895 -- Largest Magic Square
//Approach (Simulate trying all squares - optimise using prefix sums)
//T.C : O(rows * cols * min(rows, cols)^2) --> check my video for its explanation
//S.C : O(rows * cols)
class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // Row wise Prefix Sum
        vector<vector<int>> rowCumsum(rows, vector<int>(cols));
        for (int i = 0; i < rows; ++i) {
            rowCumsum[i][0] = grid[i][0];
            for (int j = 1; j < cols; ++j) {
                rowCumsum[i][j] = rowCumsum[i][j - 1] + grid[i][j];
            }
        }

        // Column wise Prefix Sum
        vector<vector<int>> colCumsum(rows, vector<int>(cols));
        for (int j = 0; j < cols; ++j) {
            colCumsum[0][j] = grid[0][j];
            for (int i = 1; i < rows; ++i) {
                colCumsum[i][j] = colCumsum[i - 1][j] + grid[i][j];
            }
        }

        // I am iterating from largest side to smallest because
        // as soon as I get a magic square, it will be largest and I will return from there
        for (int side = min(rows, cols); side >= 2; side--) {
            
            // Check square of length = side starting from all possible cells
            for (int i = 0; i + side - 1 < rows; ++i) {
                for (int j = 0; j + side - 1 < cols; ++j) {

                    int targetSum = rowCumsum[i][j + side - 1] - (j > 0 ? rowCumsum[i][j - 1] : 0);

                    bool allSame = true;

                    // Check rows
                    for (int r = i + 1; r < i + side; ++r) {
                        int rowSum = rowCumsum[r][j + side - 1] - (j > 0 ? rowCumsum[r][j - 1] : 0);
                        if (rowSum != targetSum) {
                            allSame = false;
                            break;
                        }
                    }
                    if (!allSame) 
                        continue;

                    // Check columns
                    for (int c = j; c < j + side; ++c) {
                        int colSum = colCumsum[i + side - 1][c] - (i > 0 ? colCumsum[i - 1][c] : 0);
                        if (colSum != targetSum) {
                            allSame = false;
                            break;
                        }
                    }
                    if (!allSame) 
                        continue;

                    // Check diagonals
                    int diag     = 0;
                    int antiDiag = 0;
                    for (int k = 0; k < side; ++k) {
                        diag += grid[i + k][j + k];
                        antiDiag += grid[i + k][j + side - 1 - k];
                    }

                    if (diag == targetSum && antiDiag == targetSum) {
                        return side;
                    }
                }
            }
        }

        return 1;
    }
};


// LeetCode 1292 -- Maximum Side Length of a Square with Sum Less than or Equal to Threshold
//Approach-2 (Using 2D Prefix Sum and binarysearch the square side)
//T.C : O(rows * cols * log(min(rows, cols)))
//S.C : O(rows * cols)
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int rows = mat.size();
        int cols = mat[0].size();

        // Build prefix sum
        vector<vector<int>> prefix(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                prefix[i][j] = mat[i][j]
                             + (i > 0 ? prefix[i - 1][j] : 0)
                             + (j > 0 ? prefix[i][j - 1] : 0)
                             - (i > 0 && j > 0 ? prefix[i - 1][j - 1] : 0);
            }
        }

        // Sum of square (r1,c1) -> (r2,c2)
        auto sumSquare = [&](int r1, int c1, int r2, int c2) {
            int sum = prefix[r2][c2];
            if (r1 > 0) sum -= prefix[r1 - 1][c2];
            if (c1 > 0) sum -= prefix[r2][c1 - 1];
            if (r1 > 0 && c1 > 0) sum += prefix[r1 - 1][c1 - 1];
            return sum;
        };

        // Check function
        auto check = [&](int side) {
            for (int i = 0; i + side - 1 < rows; i++) {
                for (int j = 0; j + side - 1 < cols; j++) {
                    if (sumSquare(i, j,
                                  i + side - 1,
                                  j + side - 1) <= threshold) {
                        return true;
                    }
                }
            }
            return false;
        };

        // Binary search on side length
        int lo = 1, hi = min(rows, cols);
        int result = 0;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (check(mid)) {
                result = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return result;
    }
};


// Leetcode 3314 --  Construct the Minimum Bitwise Array I
//Approach (Brute Force All Possible Answers)
//T.C : O(n)
//S.C : O(1)
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> result;


        for(int &num : nums) {
            if(num == 2) {
                result.push_back(-1);
                continue;
            }

            bool found = false;
            for(int j = 1; j < 32; j++) {
                if((num & (1 << j)) > 0) { //set bit
                    continue;
                }

                //we found an unset bit at jth position
                result.push_back((num ^ (1 << (j-1)))); //set the first set bit to 0
                found = true;
                break;
            }

            if(!found)
                result.push_back(-1);
        }

        return result;
    }
};


// Leetcode -- 3315 -- Construct the Minimum Bitwise Array I & II
//Approach (Brute Force All Possible Answers)
//T.C : O(n)
//S.C : O(1)
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> result;


        for(int &num : nums) {
            if(num == 2) {
                result.push_back(-1);
                continue;
            }

            bool found = false;
            for(int j = 1; j < 32; j++) {
                if((num & (1 << j)) > 0) { //set bit
                    continue;
                }

                //we found an unset bit at jth position
                result.push_back((num ^ (1 << (j-1)))); //set the first set bit to 0
                found = true;
                break;
            }

            if(!found)
                result.push_back(-1);
        }

        return result;
    }
};


// Leetcode 3507. Minimum Pair Removal to Sort Array I
//T.C : O(n^2)
//S.C : O(1)
class Solution {
public:
    int minPairSum(vector<int>& nums) {
        int minSum = INT_MAX;
        int index = -1;

        for(int i = 0; i < nums.size()-1; i++) {
            if(nums[i] + nums[i+1] < minSum) {
                index = i;
                minSum = nums[i] + nums[i+1];
            }
        }

        return index;
    }
    int minimumPairRemoval(vector<int>& nums) {
        int operations = 0;

        while(!is_sorted(begin(nums), end(nums))) {
            int index = minPairSum(nums);

            nums[index] = nums[index] + nums[index+1];

            nums.erase(begin(nums) + index + 1);

            operations++;
        }

        return operations;
    }
};



//Leetcode 3510. Minimum Pair Removal to Sort Array II
class Solution {
public:
    typedef long long ll;

    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();

        //{a, b, c, d} --> {a, b+c, d}
        vector<ll> temp(n);
        for(int i = 0; i < n; i++)
            temp[i] = nums[i];

        set<pair<ll, int>> minPairSet;

        vector<int> nextIndex(n);
        vector<int> prevIndex(n);

        for(int i = 0; i < n; i++) {
            nextIndex[i] = i+1;
            prevIndex[i] = i-1;
        }

        int badPairs = 0;
        for(int i = 0; i < n-1; i++) {
            if(temp[i] > temp[i+1]) {
                badPairs++;
            }
            minPairSet.insert({temp[i] + temp[i+1], i});
        }

        int operations = 0;

        while(badPairs > 0) {
            int first  = minPairSet.begin()->second;
            int second = nextIndex[first];

            int first_left   = prevIndex[first];
            int second_right = nextIndex[second];


            minPairSet.erase(begin(minPairSet));

            if(temp[first] > temp[second]) {
                badPairs--;
            }

            //{d, (a, b)}
            if(first_left >= 0) {
                if(temp[first_left] > temp[first] &&
                temp[first_left] <= temp[first] + temp[second]) {
                    badPairs--;
                } 
                else if(temp[first_left] <= temp[first] &&
                temp[first_left] > temp[first] + temp[second]) {
                    badPairs++;
                }
            }

            //{(a, b), d}
            if (second_right < n) {
                if (temp[second_right] >= temp[second] &&
                    temp[second_right] < temp[first] + temp[second]) {
                    badPairs++;
                }
                else if (temp[second_right] < temp[second] &&
                         temp[second_right] >= temp[first] + temp[second]) {
                    badPairs--;
                }
            }

            if(first_left >= 0) {
                minPairSet.erase({temp[first_left] + temp[first], first_left});
                minPairSet.insert({temp[first_left] + temp[first] + temp[second], first_left});
            }

            if(second_right < n) {
                minPairSet.erase({temp[second] + temp[second_right], second});
                minPairSet.insert({temp[first] + temp[second] + temp[second_right], first});
                prevIndex[second_right] = first;
            }

            nextIndex[first] = second_right;
            temp[first] += temp[second];

            operations++;
        }

        return operations;
    }
};



/*
    MY YOUTUBE VIDE ON THIS Qn : https://www.youtube.com/watch?v=zpOhlTndBv0
    Company Tags               : Google
    Leetcode Link              : https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/
*/

//Approach-1 - BFS
class Solution {
public:
    vector<vector<int>> directions{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        
        queue<vector<int>> que;
        
        int i = 0, j = 0;
        que.push({i, j, k});
        
        bool visited[41][41][1601];
        //vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(k)));
        memset(visited, false, sizeof(visited));
        
        int steps = 0;
        while(!que.empty()) {
            int size = que.size();
            while(size--) {
                vector<int> temp = que.front();
                que.pop();
                int curr_i   = temp[0];
                int curr_j   = temp[1];
                int obs = temp[2];
                
                if(curr_i == m-1 && curr_j == n-1)
                    return steps;
                
                for(vector<int> &dir : directions) {
                    
                    int new_i = curr_i + dir[0];
                    int new_j = curr_j + dir[1];
                    
                    if(new_i < 0 || new_i >= m || new_j < 0 || new_j >= n)
                        continue;
                    
                    if(grid[new_i][new_j] == 0 && !visited[new_i][new_j][obs]) {
                        que.push({new_i, new_j, obs});
                        visited[new_i][new_j][obs] = true;
                    } else if(grid[new_i][new_j] == 1 && obs > 0 && !visited[new_i][new_j][obs-1]) {
                        que.push({new_i, new_j, obs-1});
                        visited[new_i][new_j][obs-1] = true;
                    }
                }
                
            }
            steps++;
        }
        
        return -1;
    }
};


// Leetcode 1200 -- Minimum Absolute Difference
class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(begin(arr), end(arr));
        vector<vector<int>> result;
        int n = arr.size();
        
        int minDiff = INT_MAX;
        for(int i = 1; i < n; i++) {
            int diff = arr[i] - arr[i-1];
            minDiff = min(diff, minDiff);
        }
        
        for(int i = 1; i<n; i++) {
            int diff = arr[i]-arr[i-1];
            
            if(diff == minDiff) {
                result.push_back({arr[i-1], arr[i]});
            }
        }
        
        
        return result;
        
    }
};


// Leetcode 3455 -- Minimum Cost to Convert String
//Approach (Dijkstra's Algorithm on Graph)
class Solution {
public:
    void dijkstra(char &source, unordered_map<char, vector<pair<char, int>>> &adj, vector<vector<long long>> &costMatrix) {

        //min-heap
        priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;

        pq.push({0, source});

        while(!pq.empty()) {
            int d        = pq.top().first;
            char adjNode = pq.top().second;
            pq.pop();

            for(auto &it : adj[adjNode]) {
                char adjNode = it.first;
                int cost      = it.second;

                if(costMatrix[source - 'a'][adjNode - 'a'] > d + cost) {
                    costMatrix[source - 'a'][adjNode - 'a'] = d + cost;
                    pq.push({d + cost, adjNode});
                }
            }

        }
        return;
    }
        //V = # of vertices
    //E = # of edges
    //O(n * (V+E)log(V))
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        unordered_map<char, vector<pair<char, int>>> adj;

        for(int i = 0; i < original.size(); i++) {
            adj[original[i]].push_back({changed[i], cost[i]});
        }

        vector<vector<long long>> costMatrix(26, vector<long long>(26, INT_MAX));

        //Populate the costMatrix using Dijkstra's Algorithm
        for(int i = 0; i < source.length(); i++) { //n
            char ch = source[i];
            dijkstra(ch, adj, costMatrix);
        }

        long long ans = 0;

        for(int i = 0; i < source.length(); i++) {
            if(source[i] == target[i]) {
                continue;
            }

            if(costMatrix[source[i] - 'a'][target[i] - 'a'] == INT_MAX) {
                return -1;
            }

            ans += costMatrix[source[i] - 'a'][target[i] - 'a'];

        }

        return ans;
    }
};


// Leetcode 3456 -- Minimum Cost to Convert String II
//Approach (Using Dijkstra's Algorithm and DP with Power of Memoization for both)
/*
N = length of sourceStr / targetStr
M = number of conversion rules (original.size())
L = number of distinct substring lengths
(L = lengthSet.size())
V = number of unique strings appearing in original and changed
E = number of edges in graph (E = M)
T.C : O(
          M                           // graph build
          + M log L                     // lengthSet
          + N² × L                      // DP overhead
          + M² × (V + E) log V          // Dijkstra
        )
  S.C : O(M² + V + E + N)
*/
class Solution {
public:
    typedef long long ll;
    typedef pair<ll, string> P;
    ll BIG_VALUE = 1e10;
    unordered_map<string, vector<pair<string, ll>>> adj; //Graph

    //start -> end -> anser
    unordered_map<string, unordered_map<string, ll>> dijkstraMemo;

    vector<ll> dpMemo;

    string sourceStr;
    string targetStr;
    set<int> validLengths;
    
    ll dijkstra(string& start, string& end) {

        if(dijkstraMemo[start].count(end)) {
            return dijkstraMemo[start][end];
        }

        //{cost, string}
        priority_queue<P, vector<P>, greater<P>> pq;
        //vector<int> result(n, INT_MAX)
        unordered_map<string, ll> result; //source to string ka cost stored
        result[start] = 0;
        pq.push({0, start});

        while(!pq.empty()) {
            ll currCost = pq.top().first;
            string node = pq.top().second;
            pq.pop();

            if(node == end) {
                break;
            }

            for(auto &edge : adj[node]) {
                string adjNode = edge.first;
                ll edgeCost = edge.second;

                if(!result.count(adjNode) || currCost + edgeCost < result[adjNode]) {
                    result[adjNode] = currCost + edgeCost;
                    pq.push({currCost+edgeCost, adjNode});
                }
            }
        }

        ll finalCost = result.count(end) ? result[end] : BIG_VALUE;

        return dijkstraMemo[start][end] = finalCost;

    }

    ll solve(int idx) {
        if(idx >= sourceStr.length())
            return 0;
        if(dpMemo[idx] != -1)
            return dpMemo[idx];

        ll minCost = BIG_VALUE;

        if(sourceStr[idx] == targetStr[idx])
            minCost = solve(idx+1);
        
        for(auto &len : validLengths) {
            if(idx + len > sourceStr.length()) {
                break;
            }

            string srcSub = sourceStr.substr(idx, len);
            string tgtSub = targetStr.substr(idx, len);

            if(!adj.count(srcSub)) {
                continue;
            }

            ll minPathCost = dijkstra(srcSub, tgtSub);
            if(minPathCost == BIG_VALUE)
                continue;
            
            minCost = min(minCost, minPathCost + solve(idx+len));
        }

        return dpMemo[idx] = minCost;
    }

    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        sourceStr = source;
        targetStr = target;

        dpMemo.assign(10001, -1);

        for(int i = 0; i < original.size(); i++) {
            adj[original[i]].push_back({changed[i], cost[i]});
        }

        for(auto &s : original) {
            validLengths.insert(s.length());
        }

        ll result = solve(0);

        return result == BIG_VALUE ? -1 : result;
    }
};


// Leetcode 744 -- Find Smallest Letter Greater Than Target
//Approach-2 (Using Own Binary Search) - TC : O(log(n))
class Solution {
public:
    
    int binarySearch(vector<char>& letters, char target) {
        int n = letters.size();
        int l = 0, r = n-1;
        
        int position = n;
        
        while(l <= r) {
            
            int mid = l + (r-l)/2;
            
            if(letters[mid] > target) {
                position = mid;
                r = mid-1;
            } else {
                l = mid+1;
            }
            
        }
        
        return position;
    }
    
    char nextGreatestLetter(vector<char>& letters, char target) {
        
        int idx = binarySearch(letters, target);
        
        if(idx == letters.size())
            return letters[0];
        
        return letters[idx];
        
    }
};


// Leetcode -- 3010 | Divide an Array Into Subarrays With Minimum Cost I 
class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int n = nums.size();
        int score = nums[0];
        int fM = INT_MAX;
        int sM = INT_MAX;

        for(int i=1; i<n; i++){
            if(nums[i] < fM){
                sM= fM;
                fM = nums[i];
            }else if(nums[i] < sM){
                sM = nums[i];
            }
        }
        return score + fM +sM;
    }
};


// Leetcode 3011 -- Divide an Array Into Subarrays With Minimum Cost II
//Approach (Sliding Window using ordered sets)
//T.C : O(n * log(k)), set operations are logarithmic
//S.C : O(k), set stores (k-1) elements
class Solution {
public:
    typedef long long ll;
    typedef pair<ll, ll> P;

    ll minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();

        set<P> kMinimum; //stores (k-1) minimum elements
        set<P> remaining;

        ll sum = 0; //stores sum of (k-1) min elements

        int i = 1;
        while(i - dist < 1) {
            kMinimum.insert({nums[i], i});
            sum += nums[i];
            if(kMinimum.size() > k-1) {
                P temp = *kMinimum.rbegin();
                sum -= temp.first;
                remaining.insert(temp);
                kMinimum.erase(temp);
            }
            i++;
        }

        ll result = LONG_MAX; //stores min sum of (k-1) elements
        //0, 1, ...... i
        while(i < n) {
            kMinimum.insert({nums[i], i});
            sum += nums[i];

            if(kMinimum.size() > k-1) {
                P temp = *kMinimum.rbegin();
                sum -= temp.first;
                remaining.insert(temp);
                kMinimum.erase(temp);
            }

            result = min(result, sum);

            //shift window
            //i-dist wala element will be removed
            P remove = {nums[i-dist], i-dist};
            if(kMinimum.count(remove)) {
                kMinimum.erase(remove);
                sum -= remove.first;

                if(!remaining.empty()) {
                    P temp = *remaining.begin();
                    kMinimum.insert(temp);
                    sum += temp.first;
                    remaining.erase(temp);
                }
            } else {
                remaining.erase(remove);
            }

            i++;
        }

        return nums[0] + result;
    }
};


// Leetcode 3637 -- Trionic Array I | Leetcode 3637
class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int n = nums.size();
        //Need to check the Ince, Dec, Ince
        int i=0;
        //Inc
        while(i+1<n && nums[i] < nums[i+1]){
            i++;
        }
        if(i == 0 || i == n-1){
            return false;
        }
        //Dec
        while(i+1 <n && nums[i]> nums[i+1]){
            i++;
        }
        if(i == n-1){
            return false;
        }
        //Increasing
        while(i+1<n && nums[i] < nums[i+1]){
            i++;
        }

        return i == n-1;
    }
};


// Leetcode 3640 -- Trionic Array II |  
class Solution {
public:
    typedef long long ll;
    int n;
    vector<vector<ll>> memo;
    ll solve(int i, int trend, vector<int>& nums){
        if(i == n){
            if(trend == 3){
                return 0;
            }else{
                return LLONG_MIN/2;
            }
        }

        if(memo[i][trend] != LLONG_MIN){
            return memo[i][trend];
        }


        ll take = LLONG_MIN/2;
        ll skip = LLONG_MIN/2;
        if(trend == 0){
            skip = solve(i+1, 0, nums);
        }
        if(trend == 3){
            take = nums[i];
        }
        if(i+1 <n){
            int curr = nums[i];
            int next = nums[i+1];
            if(trend ==0 && next > curr){
                take = max(take, curr + solve(i+1, 1, nums));
            }else if(trend == 1){
                if(next > curr){
                    take = max(take, curr + solve(i+1, 1, nums));
                }else if(next < curr){
                    take = max(take, curr + solve(i+1, 2, nums));
                }
            }else if(trend == 2){
                if(next < curr){
                    take = max(take, curr + solve(i+1, 2, nums));
                }else if(next > curr){
                    take = max(take, curr + solve(i+1, 3, nums));
                }
            }else if(trend ==3 && next > curr){
                take = max(take, curr + solve(i+1, 3, nums));
            }
        }
        return memo[i][trend] = max(take, skip);
    }
    long long maxSumTrionic(vector<int>& nums) {
        n = nums.size();
        memo.assign(n+1, vector<ll>(4, LLONG_MIN));
        return solve(0,0, nums); //solve(i, trend =0)
    }
};


// Leetcode 3379 -- Transformed Array | Cleanest Implementation | Leetcode 3379
//Approach (Iterate and find)
//T.C : O(n) 
//S.C : O(1)
class Solution {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        int n = nums.size();

        vector<int> result(n, 0);

        for(int i = 0; i < n; i++) {
            int shift = nums[i]%n; //reducing the large shifts within 0..n-1 range

            int newIdx = (i + shift) % n;

            if(newIdx < 0) {
                newIdx += n;
            }

            result[i] = nums[newIdx];
        }

        return result;

    }
};



// Leetcode 3634 -- Minimum Removals to Balance Array | Leetcode 3634
//Approach (Using sorting and two pointers)
//T.C : O(nlogn)
//S.C : O(1)
class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        int n = nums.size();
        sort(begin(nums), end(nums));

        int maxEl = nums[0];
        int minEl = nums[0];

        int L = 1;
        int i = 0;
        int j = 0;

        while(j < n) {
            maxEl = nums[j];
            minEl = nums[i];

            while(i < j && maxEl > (long long)k * minEl) {
                i++;
                minEl = nums[i];
            }

            L = max(L, j-i+1);
            j++;
        }

        return n - L;
    }
};

// Leetcode 1653 --  Minimum Deletions to Make String Balanced | Multiple Approaches | Leetcode 
//Approach-1 (Using stack)
//T.C : O(n)
//S.C : O(n)
class Solution {
public:
    int minimumDeletions(string s) {
        int n     = s.length();
        int count = 0;

        stack<char> st;

        for(int i = 0; i < n; i++) {
            if(!st.empty() && s[i] == 'a' && st.top() == 'b') { //'ba'
                st.pop();
                count++;
            } else {
                st.push(s[i]);
            }
        }

        return count;
    }
};


//Approach-2 (3 Pass + O(2*n) space)
//T.C : O(3*n)
//S.C : O(2*n)
class Solution {
public:
    int minimumDeletions(string s) {
        int n     = s.length();
        
        vector<int> left_b(n, 0);
        vector<int> right_a(n, 0);

        int countb = 0;
        for(int i = 0; i < n; i++) {
            left_b[i] = countb;
            if(s[i] == 'b')
                countb++;
        }

        int counta = 0;
        for(int i = n-1; i >= 0; i--) {
            right_a[i] = counta;
            if(s[i] == 'a')
                counta++;
        }

        int count = INT_MAX;
        for(int i = 0; i < n; i++) {
            count = min(count, left_b[i] + right_a[i]);
        }

        return count;
    }
};


//Approach-3 (2 Pass + O(n) space)
//T.C : O(2*n)
//S.C : O(n)
class Solution {
public:
    int minimumDeletions(string s) {
        int n     = s.length();
        
        vector<int> right_a(n, 0);

        
        int counta = 0;
        for(int i = n-1; i >= 0; i--) {
            right_a[i] = counta;
            if(s[i] == 'a')
                counta++;
        }

        int count = INT_MAX;
        int countb = 0;

        for(int i = 0; i < n; i++) {
            count = min(count, countb + right_a[i]);
            if(s[i] == 'b')
                countb++;
        }

        return count;



    }
};


//Approach-4 (Constant space)
//T.C : O(2*n)
//S.C : O(1)
class Solution {
public:
    int minimumDeletions(string s) {
        int n     = s.length();

        
        int counta = 0;
        for(int i = n-1; i >= 0; i--) {
            if(s[i] == 'a')
                counta++;
        }

        int count = INT_MAX;
        int countb = 0;

        for(int i = 0; i < n; i++) {
            if(s[i] == 'a')
                counta--;
            count = min(count, countb + counta);

            if(s[i] == 'b')
                countb++;
        }

        return count;
    }
};

// Leetcode 110 Balanced Binary Tree | Simple Clean Approach |  
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
    int height(TreeNode* root){
        if(!root) return 0;
        int leftH = height(root->left);
        int rightH = height(root->right);
        return max(leftH, rightH) +1;
    }
    bool isBalanced(TreeNode* root) {
        if(!root) return true;

        int leftH = height(root->left);
        int rightH= height(root->right);

        if(abs(rightH - leftH) >1) return false;

        return isBalanced(root->left) && isBalanced(root->right);
    }
};


// Leecode 1382 -- Balance a Binary Search Tree | Leetcode 1382
// TC o(n), sc- o(n)
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
    TreeNode* solve(int l, int r, vector<int>& vec){
        if(l>r) return NULL;

        int mid = l + (r-l)/2;
        TreeNode* root = new TreeNode(vec[mid]);
        root->left = solve(l, mid-1, vec);
        root->right =  solve(mid+1, r, vec);

        return root;
    }
    void inOrder(TreeNode* root, vector<int>& vec){
        if(!root) return;
        inOrder(root->left, vec);
        vec.push_back(root->val);
        inOrder(root->right, vec);
    }
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> vec;
        inOrder(root, vec);
        
        int l =0;
        int r = vec.size()-1;
        return solve(l, r, vec);
    }
};


// Leetcode 3719 -- Longest Balanced Subarray I | Leetcode 3719
class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();

        int maxLen = 0;
        for(int i =0; i<n; i++){
            unordered_set<int> even;
            unordered_set<int> odd;
            for(int j=i; j<n; j++){
                if(nums[j]%2 == 0){
                    even.insert(nums[j]);
                }else{
                    odd.insert(nums[j]);
                }

                if(even.size() == odd.size()){
                    maxLen = max(maxLen, j-i+1);
                }
            }
        }
        return maxLen;
    }
};



// Longest Balanced Subarray II | Leetcode 3721 | Min-Max Query | Segment Tree Concept | Video 15
//Approach - 2 (Using Segment Tree RMin Max Query
//T.C : O(nlogn)
//S.C : O(n)
class Solution {
public:

    vector<int> segMin, segMax, lazy;
    int n;

    void propagate(int i, int l, int r) {
        if (lazy[i] != 0) {
            segMin[i] += lazy[i];
            segMax[i] += lazy[i];

            if (l != r) {
                lazy[2*i+1] += lazy[i];
                lazy[2*i+2] += lazy[i];
            }
            lazy[i] = 0;
        }
    }

    // Range add val to [start, end]
    void updateRange(int start, int end, int i, int l, int r, int val) {
        propagate(i, l, r); //make sure to propagate before hand

        if (l > end || r < start) return;

        //[start...end[ is fully inside range of current node [l..r]
        if (l >= start && r <= end) {
            lazy[i] += val;
            propagate(i, l, r);
            return;
        }

        int mid = (l + r) / 2;
        updateRange(start, end, 2*i+1, l, mid, val);
        updateRange(start, end, 2*i+2, mid+1, r, val);

        segMin[i] = min(segMin[2*i+1], segMin[2*i+2]);
        segMax[i] = max(segMax[2*i+1], segMax[2*i+2]);
    }

    int findLeftMostZero(int i, int l, int r) {
        propagate(i, l, r);

        if(segMin[i] > 0 || segMax[i] < 0) {
            return -1;
        }

        if(l == r) {
            return l;
        }

        int mid = l + (r-l)/2;
        int leftResult = findLeftMostZero(2*i+1, l, mid);
        if(leftResult != -1)
            return leftResult;
        
        return findLeftMostZero(2*i+2, mid+1, r);
    }

    int longestBalanced(vector<int>& nums) {
        n = nums.size();
        segMin.assign(4*n, 0);
        segMax.assign(4*n, 0);
        lazy.assign(4*n, 0);

        //treating even = +1 and odd = -1
        vector<int> cumSum(n, 0);

        int maxL = 0;

        unordered_map<int, int> mp;

        for(int r = 0; r < n; r++) {
            int val = (nums[r] % 2 == 0) ? 1 : -1;

            int prev = -1;
            if(mp.count(nums[r])) {
                prev = mp[nums[r]];
            }

            if(prev != -1) { //we have seen this element in past
                //[0..prev] we are adding (-val) in the range
                updateRange(0, prev, 0, 0, n-1, -val);
            }

            //[0...r] we are adding val in the range
            updateRange(0, r, 0, 0, n-1, val);

            //We are finding left most 0 in the range [0...r]
            int l = findLeftMostZero(0, 0, n-1);
            if(l != -1)
                maxL = max(maxL, r-l+1);

            mp[nums[r]] = r;
        }

        return maxL;
    }
};


// Leetcode 3713 -- Longest Balanced Subarray I | Leetcode 3713
//Approach (try all subarrays)
//T.C : O(n^2)
//S.C : O(1)
class Solution {
public:

    bool checkBalanced(vector<int>& freq) {
        int common = 0;
        for(int i = 0; i < 26; i++) {
            if(freq[i] == 0) continue;
            if(common == 0)
                common = freq[i];
            else if(freq[i] != common) {
                return false;
            }
        }

        return true;
    }

    int longestBalanced(string s) {
        int n = s.length();

        int maxL = 0;

        for(int i = 0; i < n; i++) {
            vector<int> freq(26, 0);

            for(int j = i; j < n; j++) {
                freq[s[j] - 'a']++;

                //i..j
                if(checkBalanced(freq)) {
                    maxL = max(maxL, j-i+1);
                }
            }
        }

        return maxL;
    }
};



// Leetcode 3714 -- Longest Balanced Subarray II | Leetcode 3714
//Approach (storing diff in Map)
//T.C : O(nlogn)
//S.C : O(n)
class Solution {
public:
    int helper(string&s, int ch1, int ch2) {
        int n = s.length();
        unordered_map<int, int> diffMap;
        int maxL = 0;
        int count1 = 0;
        int count2 = 0;

        for(int i = 0; i < n; i++) {
            if(s[i] != ch1 && s[i] != ch2) {
                diffMap.clear();
                count1 = 0;
                count2 = 0;
                continue;
            }

            if(s[i] == ch1)
                count1++;
            if(s[i] == ch2)
                count2++;

            if(count1 == count2) {
                maxL = max(maxL, count1+count2);
            }

            int diff = count1 - count2;
            if(diffMap.count(diff)) {
                maxL = max(maxL, i - diffMap[diff]);
            } else {
                diffMap[diff] = i;
            }
        }
        
        return maxL;
    }

    int longestBalanced(string s) {
        int n    = s.length();
        int maxL = 0;

        //Case-1
        //"aaaa"
        int count = 1; //s[0]
        for(int i = 1; i < n; i++) {
            if(s[i] == s[i-1]) {
                count++;
            } else {
                maxL = max(maxL, count);
                count = 1;
            }
        }
        maxL = max(maxL, count);

        //Case-2
        maxL = max(maxL, helper(s, 'a', 'b'));
        maxL = max(maxL, helper(s, 'a', 'c'));
        maxL = max(maxL, helper(s, 'b', 'c'));


        //Case-3
        int countA = 0;
        int countB = 0;
        int countC = 0;
        unordered_map<string, int> diffMap;

        for(int i = 0; i < n; i++) {
            if(s[i] == 'a')
                countA++;
            if(s[i] == 'b')
                countB++;
            if(s[i] == 'c')
                countC++;

            if(countA == countB && countA == countC) {
                maxL = max(maxL, countA+countB+countC);
            }

            int diffAB = countA - countB;
            int diffAC = countA - countC;

            string key = to_string(diffAB) + "_" + to_string(diffAC); //log(n) digits

            if(diffMap.count(key)) {
                maxL = max(maxL, i - diffMap[key]);
            } else {
                diffMap[key] = i;
            }
        }

        return maxL;

    }
};
