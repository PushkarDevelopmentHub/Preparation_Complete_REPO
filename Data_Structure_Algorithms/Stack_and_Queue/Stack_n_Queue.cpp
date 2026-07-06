



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
}