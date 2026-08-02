//convert to Binary
string convertToBinary(int m){
  string ans = "";
  while(m > 0){
    ans += to_string(m%2);
    m /= 2;
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

//convert to Decimal
int convert2Decimal(string s){
  int ans = 0;
  int n = s.length();
  for(int i = 0; i<n; i++){
    if(s[i] == '1'){
      ans += pow(2, n-i-1);
    }
  }
  return ans;
}

// Swap two numbers without third variable
void swap(int &a, int&b){
  a= a^b;
  b = a^b;
  a = a^b;
}

// Check if the ith bit is set or not
bool isSet(int n, int i){
  return (n & (1<<i)) != 0;
}

//set the ith bit
int setBit(int n, int i){
  return (n | (1<<i));
}

//clear the ith bit
int clearBit(int n, int i){
 return (n & ~(1<<i)); 
}

//Toggle the ith bit
int toggleBit(int n, int i){
  return (n ^ (1<<i));
}

//Remove the last set bit(right most)
int removeLastSetBit(int n){
  return (n & (n-1));
}

//check if number is power of 2
bool ispowerof2(int n){
  return (n && !(n & (n-1)));
}

//