// Binary Search
#include <bits/stdc++.h>
using namespace std;

class Solution{
  public: 
  int binarySearch(vector<int>& nums, int target){
    int n= nums.size();
    int low = 0, high = n-1;
    while(low<= high){

      int mid = low + (high-low)/2;
      if(nums[mid] == target) return mid;
      else if(nums[mid] < target) low = mid+1;
      else high = mid-1;
    }
    return -1;
  }
};

int main(){
  vector<int> a = {3, 4, 6, 7, 9, 12, 16, 17}; // sorted array
    int target = 6; // target element to search
  Solution obj;
  int ind = obj.binarySearch(a, target);
  
  if(ind == -1) cout<< "Not target Present "<<endl;
  else cout<< "target at "<< ind <<endl;
}


// Lower Bound
#include <bits/stdc++.h>
using namespace std;

// Class containing methods for array operations
class LowerBoundFinder {
public:
  int lowerBound(vector<int> arr, int n, int x) {
      int l = 0, h= n-1;
      int ans=n;
      while(l<=h){
        int mid = l+ (h-l)/2;
        if(arr[mid] >= x){
          ans = mid;
          h= mid-1;
        } else{
          l= mid+1;
        }
      }
      return ans;
  }
};

int main() {
    vector<int> arr = {3, 5, 8, 15, 19};
    int n = arr.size();  // Size of the array
    int x = 9;           // Target value

    LowerBoundFinder finder;                  // Create object
    int ind = finder.lowerBound(arr, n, x);   // Find lower bound index

    cout << "The lower bound is the index: " << ind << "\n";

    return 0;
}


//Upper Bound
#include <bits/stdc++.h>
using namespace std;

// Class to compute upper bound
class UpperBoundFinder {
public:
    // Function to find the upper bound using binary search
    int upperBound(vector<int> &arr, int x, int n) {
        int low = 0, high = n - 1;
        int ans = n;  // Default answer if x is >= all elements

        while (low <= high) {
            int mid = (low + high) / 2;

            if (arr[mid] > x) {
                ans = mid;        // Potential answer found
                high = mid - 1;   // Try to find smaller valid index on the left
            } else {
                low = mid + 1;    // Move right if mid is <= x
            }
        }
        return ans;  // Index of the first element > x
    }
};

int main() {
    vector<int> arr = {3, 5, 8, 9, 15, 19};  // Sorted input array
    int n = arr.size();                     // Size of the array
    int x = 9;                              // Target value

    UpperBoundFinder finder;               // Create object
    int ind = finder.upperBound(arr, x, n);  // Call method

    cout << "The upper bound is the index: " << ind << "\n";  // Output result
    return 0;
}

//Floor and Ceil in Sorted Array
#include <bits/stdc++.h>
using namespace std;

class FloorCeilFinder {
public:
    // Function to find the floor of x
    int findFloor(int arr[], int n, int x) {
        int low = 0, high = n - 1;
        int ans = -1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] <= x) {
                ans = arr[mid];     // Potential floor
                low = mid + 1;      // Search right side
            } else {
                high = mid - 1;     // Search left side
            }
        }
        return ans;
    }

    // Function to find the ceiling of x
    int findCeil(int arr[], int n, int x) {
        int low = 0, high = n - 1;
        int ans = -1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] >= x) {
                ans = arr[mid];     // Potential ceil
                high = mid - 1;     // Search left side
            } else {
                low = mid + 1;      // Search right side
            }
        }
        return ans;
    }

    // Function to return both floor and ceil
    pair<int, int> getFloorAndCeil(int arr[], int n, int x) {
        int f = findFloor(arr, n, x);
        int c = findCeil(arr, n, x);
        return make_pair(f, c);
    }
};

int main() {
    int arr[] = {3, 4, 4, 7, 8, 10};
    int n = 6, x = 5;
    FloorCeilFinder finder;
    pair<int, int> ans = finder.getFloorAndCeil(arr, n, x);
    cout << "The floor and ceil are: " << ans.first << " " << ans.second << endl;
    return 0;
}


//Last occurrence in a sorted array
#include <bits/stdc++.h>
using namespace std;

// find last index of key using binary search
int solve(int n, int key, vector<int>& v) {
  // initialize search bounds and result
  int start = 0;
  int end = n - 1;
  int res = -1;

  // binary search loop
  while (start <= end) {
    // compute mid safely
    int mid = start + (end - start) / 2;
    // when match found, store index and move right
    if (v[mid] == key) {
      res = mid;
      start = mid + 1;
    }
    // when key is smaller, move left
    else if (key < v[mid]) {
      end = mid - 1;
    }
    // otherwise move right
    else {
      start = mid + 1;
    }
  }
  // return last occurrence or -1
  return res;
}

// program entry
int main() {
  // define input size and key
  int n = 7;
  int key = 13;
  // define sorted array
  vector<int> v = {3, 4, 13, 13, 13, 20, 40};
  // print last occurrence index (or -1)
  cout << solve(n, key, v) << "\n";
  // exit
  return 0;
}
