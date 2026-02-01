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
