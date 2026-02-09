// Question - 1 -- String Compression | Leetcode 443
class Solution {
public:
    int compress(vector<char>& chars) {
       int n = chars.size();
       int index = 0;
       int i = 0;
       while(i<n){
        char curr_char = chars[i];
        int count = 0;
        while(i<n && chars[i] == curr_char){
            count++;
            i++;
        }
        chars[index] = curr_char;
        index++;
        if(count >1){
            string count_str = to_string(count);
            for(char &ch: count_str){
                chars[index] = ch;
                index++;
            }
        }
       } 
       return index;
    }
};

// Question - 2 -- Check if the Sentence Is Pangram | Leetcode 1832
class Solution {
public:
    bool checkIfPangram(string sentence) {
       int n = sentence.length(); 
       vector<int> arr(26, 0);
       for(char &ch : sentence){
        int index = ch - 'a';
        arr[index]++;
       }
       for(int &count : arr){
        if(count ==0)
            return false;
       }

       return true;
    }
};
class Solution {
public:
    bool checkIfPangram(string sentence) {
       int n = sentence.length(); 
       vector<int> arr(26, 0);
       int count = 0;
       for(char &ch : sentence){
        int index = ch - 'a';
        if(arr[index] ==0){
            arr[index]++;
            count++;
        }
       } 

       if(count ==26) return true;
       
       return false;
    }
};


// Count and Say | Made Super Easy | Simple Explanation | Leetcode 38
class Solution {
public:
    string countAndSay(int n) {
 /*
 countAndSay(1) = "1"
countAndSay(2) = RLE of "1" = "11" ek barr ek likha hai
countAndSay(3) = RLE of "11" = "21" do bar ek likha hia
countAndSay(4) = RLE of "21" = "1211" ek barr 2 likha hai 1 bar ek likah hai
 */       
      if(n == 1) return "1";
      string say = countAndSay(n-1);
      
      //processing
      string result = "";
      for(int i=0; i<say.length(); i++){
        char ch = say[i];
        int count =1;
        while(i< say.length() -1 && say[i] == say[i+1]){
            count++; 
            i++;
        }
        result += to_string(count) + string(1, ch);
      }
    return result;
    }
};



// Leetcode 12 -- Integer to Roman
class Solution {
public:
//      vector<int> val{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
//      vector<string> sym{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
  
    string intToRoman(int num) {
         static vector<int> val{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  static  vector<string> sym{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        string res = "";
        for(int i=0; i<13; i++){
            if(num == 0) break;
            int times = num/val[i];
            while(times--){
                res += sym[i];
            }
            num = num%val[i];
        }
        return res;
    }
};