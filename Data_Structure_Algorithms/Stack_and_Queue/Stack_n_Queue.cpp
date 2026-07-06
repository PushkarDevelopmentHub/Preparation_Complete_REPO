#include <bits/stdc++.h>
using namespace std;
//L3. Prefix, Infix, and Postfix Conversion | Stack and Queue Playlist
// x+pq-mn(Prefix)    (p+q)*(m-n)(Infix)    pq+mn-*(Postfix)
//Infix to Postfix
int precedence(char op)
{
    if(op == '+' || op == '-')
        return 1;

    if(op == '*' || op == '/')
        return 2;

    if(op == '^')
        return 3;

    return 0;
}
string infixToPostfix(string infix){
    stack<char> st;
    string postfix = "";
    for(int i =0; i<infix.length(); i++){
        char c= infix[i];
        if(c>='a' && c<='z' || c>='A' && c<='Z' || c>='0' && c<='9'){
            postfix+=c;
        }
        else if(c=='('){
            st.push('(');
        }
        else if(c==')'){
            while(!st.empty() && st.top()!='('){
                postfix+=st.top();
                st.pop();
            }
            st.pop();
        }
        else{
            while(!st.empty() && precedence(st.top())>=precedence(c)){
                postfix+=st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while(!st.empty()){
        postfix+=st.top();
        st.pop();
    }
    return postfix;
}

//Postfix to Infix
bool operand(char c){
    return (c>='a' && c<='z' || c>='A' && c<='Z' || c>='0' && c<='9');
}
string postfixToInfix(string postfix){
    stack<string> st;
    for(int i =0; i<postfix.length(); i++){
        char c= postfix[i];
        if(operand(c)){
            string op(1, c);
            st.push(op);
        }
        else{
            string op2 = st.top(); st.pop();
            string op1 = st.top(); st.pop();
            string exp = "(" + op1 + c + op2 + ")";
            st.push(exp);
        }
    }
    return st.top();
}

TC-> O(N) + O(N) SC-> O(N)


//Prefix to Infix
string prefixToInfix(string prefix){
    stack<string> st;
    for(int i = prefix.length()-1; i>=0; i--){
        char c= prefix[i];
        if(operand(c)){
            string op(1, c);
            st.push(op);
        }
        else{
            string op1 = st.top(); st.pop();
            string op2 = st.top(); st.pop();
            string exp = "(" + op1 + c + op2 + ")";
            st.push(exp);
        }
    }
    return st.top();
}


//Postfix to Prefix
string postfixToPrefix(string postfix){
    stack<string> st;
    for(int i=0; i<postfix.length(); i++){
        char c = postfix[i];
        if(operand(c)){
            string op(1, c);
            st.push(op);
        }
        else{
            string op2 = st.top(); st.pop();
            string op1 = st.top(); st.pop();
            string exp = c + op1 + op2;
            st.push(exp);
        }
    }
    return st.top();
}
TC-> O(N) + O(N) SC-> O(N)

//Prefix to Postfix
string prefixToPostfix(string prefix){
    stack<string> st;
    for(int i=prefix.length()-1; i>=0; i--){
        char c = prefix[i];
        if(operand(c)){
            string op(1, c);
            st.push(op);
        }
        else{
            string op1 = st.top(); st.pop();
            string op2 = st.top(); st.pop();
            string exp = op1 + op2 + c;
            st.push(exp);
        }
    }
    return st.top();
}

TC-> O(N) + O(N) SC-> O(N)


//L4. Implement Min Stack | Stack and Queue Playlist
class MinStack {
    public:
    stack<pair<int, int>> st;

    void push(int x) {
        if(st.empty()){
            st.push({x, x});
        }
        else{
            int minVal = min(x, st.top().second);
            st.push({x, minVal});
        }
    }

    getMin(){
        st.top().second;
    }

    top(){
        st.top().first;
    }
}
TC-> O(1) SC-> O(N)


//L2. Check for Balanced Parentheses | Stack and Queue
bool checkforBalancedParenthese(string str){
  stack<char> st;
  for(int i=0; i<str.size(); i++){
    if(str[i] == '(' || str[i] == '[' || str[i] == '{'){
      st.push(str[i]);
    }else{
      if(st.empty()) return false;
      char ch = st.top();
      st.pop();
      if((str[i] == '(' && str[i] == ')') || (str[i] == '[]' && str[i] == ']') || (str[i] == '{}' && str[i] == '}')){
        continue;
      }else{
        return false;
      }
    }
  }
  return st.empty();
}

TC-> O(N) SC-O(N)


//L3. Prefix, Infix, and Postfix Conversion | Stack and Queue Playlist
//convert infix to postfix
string infixtoPostfix(string s){
  int i =0; string st;
  string ans = "";
  while (i<s.size()){
    if((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')
    || (s[i] >= '0' && s[i] <= '9')){
      ans = ans + s[i];
    }else if(s[i] == '('){
      st.push(s[i]);
    }else if(s[i] == ')'){
      while(st.empty() && st.top() != '('){
        ans += st.top();
        st.pop();
      }
      st.pop();
    }else{
      while(st.empty() && priority)
    }
  }
  
}





//L5. Next Greater Element | Stack and Queue Playlist
vector<int> nextGreaterElement(vector<int>& arr){
  int n = arr.size();
  vector<int> ans(n, -1);
  stack<int> st;
  for(int i=n-1; i>=0; i--){
    while(!st.empty() && st.top() <= arr[i]){
      st.pop();
    }
    if(st.empty()){
      ans[i] = -1;
    }else{
      ans[i] = st.top();
    }
    st.push(arr[i]);
  }
  return ans;
}

TC-> O(2N) SC-> O(N)


//L6. Next Greater Element - II | Stack and Queue Playlist
vector<int> findNextGreaterElements(vector<int>& nums){
  int n = nums.size();
  vector<int> ans(n, -1);
  stack<int> st;

  for(int i=2*n-1; i>=0; i--){
    while(!st.empty() && st.top() <= nums[i%n]){
      st.pop();
    }
    if(i<n){
      if(st.empty()){
        ans[i] = -1;
      }else{
        ans[i] = st.top();
      }
    }
  st.push(arr[i%n]);
  }
  return ans;
}

TC-> O(2N) SC-> O(N)


//L7. Previous Smaller Element | Stack and Queue Playlist
vector<int> previousSamllestElement(vector<int>& arr){
  int n = arr.size();
  vector<int> ans(n, -1);
  stack<int> st;
  for(int i=0; i<n; i++){
    while(!st.empty() && st.top() >= arr[i]){
      st.pop();
    }
    ans[i] = st.empty() ? -1 : st.top();
    st.push(arr[i]);
  } 
  return ans;
}

TC -> O(N) SC-> O(N)


//L8. Trapping Rainwater | 2 Approaches | Stack and Queue Playlist
int trapRainwater(vector<int>& height){
  int n = height.size();
  int leftMax  = rightMax  = total = 0;
  int left = 0, right = n-1;
  while(left <= right){
    if(height[left] <= height[right]){
      if(leftMax > height[left]){
        total += leftMax - height[left];
      }else{
        leftMax = height[left];
      }
      left++;
    }else{
      if(rightMax > height[right]){
        total += rightMax - height[right];
      }else{
        rightMax = height[right];
      }
      right--;
    }
  }
  return total;
}

TC -> O(N) SC-> O(1)


//L9. Sum of Subarray Minimum | Stack and Queue Playlist
int sumSubarrayMinimum(vector<int>& arr){
  int n = arr.size();
  vector<int> nextSmallerElement = findNextGreaterElements(arr);
  vector<int> previousSmallerElement = previousSamllestElement(arr);

  int totalSum = 0, mod= 1e9+ 7;
  for(int i=0; i<n; i++){
    int left = i - previousSmallerElement[i];
    int right = nextSmallerElement[i] - i;
    totalSum += (arr[i] * left * right * 1LL) % mod;
  }
  return totalSum;
}

TC -> O(5N) SC-> O(3N)

int sumSubarrayMaximum(vector<int>& arr){
  int n = arr.size();
  vector<int> nextGreaterElement = findNextGreaterElements(arr);
  vector<int> previousGreaterElement = previousSamllestElement(arr);

  int totalSum = 0, mod = 1e9+ 7;
  for(int i=0; i<n; i++){
    int left = i - previousGreaterElement[i];
    int right = nextGreaterElement[i] - i;
    totalSum += (arr[i] * left * right * 1LL) % mod;
  }
  return totalSum;
}

//L10. Sum of subarray ranges | Stack and Queue Playlist
int sumOfSubarrayRanges(vector<int>& arr){
  int n = arr.size();
  int sumSubarrayMinimum = sumSubarrayMinimum(arr);
  int sumSubarrayMaximum = sumSubarrayMaximum(arr);

  return sumSubarrayMaximum - sumSubarrayMinimum;
}

//L11. Aestroid Collisions | Stack and Queue Playlist
vector<int> asteroidCollision(vector<int>& asteroids){
  stack<int> st;
  for(int i=0; i<asteroids.size(); i++){
    if(asteroids[i] > 0){
      st.push(asteroids[i]);
    }else{
      while(!st.empty() && st.top() > 0 && st.top() < abs(asteroids[i])){
        st.pop();
      }
      if(!st.empty() && st.top() == abs(asteroids[i])){
        st.pop();
      }else if(st.empty() || st.top() < 0){
        st.push(asteroids[i]);
      }
    }
  }
  vector<int> ans(st.size());
  for(int i=st.size()-1; i>=0; i--){
    ans[i] = st.top();
    st.pop();
  }
  return ans;
}

TC-> O(N) SC-> O(N)


//L12. Largest Rectangle in Histogram | Stack and Queue Playlist
vector<int> nextSmallerElement(vector<int>& arr){
  int n = arr.size();
  vector<int> ans(n,n);
  stack<int> st;
  for(int i=0; i<n; i++){
    while(!st.empty() && arr[st.top()] >= arr[i]){
      ans[st.top()] = i;
      st.pop();
    }

    st.push(i);
  }
  return ans;
}

int largestRectangleArea(vector<int>& heights){
  int n = heights.size();
  vector<int> nextSmaller = nextSmallerElement(heights);
  vector<int> previousSmaller = previousSamllestElement(heights);

  int maxArea = 0;
  for(int i=0; i<n; i++){
    int width = nextSmaller[i] - previousSmaller[i] - 1;
    int area = heights[i] * width;
    maxArea = max(maxArea, area);
  }
  return maxArea;
}

TC -> O(5N) SC-> O(3N)


int largestRectangleArea(vector<int& heights){
  stack<int> st;
  int maxArea = 0;

  for(int i =0; i<heights.size(); i++){
    while(!st.empty() && heights[st.top()] > heights[i]){
      int height = heights[st.top()];
      st.pop();
      int nextsamller = i;
      int previsoussamller= st.empty() ? -1 : st.top();

      int width = nextsmaller - previsoussamller - 1;
      int area = height* width;
      maxArea = max(maxArea, area);
    }
    while(!st.empty()){
      int height = heights[st.top()];
      st.pop();
      int nextSmaller = heights.size();
      int previousSmaller = st.empty() ? -1 : st.top();
      int width = nextSmaller - previousSmaller - 1;
      int area = height * width;
      maxArea = max(maxArea, area);
    }
  }
  return maxArea;
}

TC-> O(2N) SC-> O(N)


