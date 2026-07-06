#include<bits/stdc++.h>
using namespace std;


void pattern1(int n){
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cout<<"*";
    }
    cout<<endl;
  }
}
void pattern2(int n){
  for(int i=0; i<=n; i++){
    for(int j=0; j<=i; j++){
      cout<<"*";
    }
    cout<<endl;
  }
}
void pattern3(int n){
  for(int i=1; i<=n; i++){
    for(int j=1; j<=i; j++){
      cout<<j;
    }
    cout<<endl;
  }
}

void pattern4(int n){
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n-i+1; j++){
      cout<<j;
    }
    cout<<endl;
  }
}

void pattern5(int n){
  //pyramid pattern
  for(int i=0; i<=n; i++){
     
    for(int j=0; j<=n-i; j++){
      cout<<" ";
    }
    for(int k =0; k<2*i+1; k++){
      cout<<"*";
    }
    cout<<endl;
  }
}

void pattern6(int n){
  //pyramid pattern reverse
  for(int i=0; i<=n; i++){
     
    for(int j=0; j<=i; j++){
      cout<<" ";
    }
    for(int k =0; k<=2*n-2*i; k++){
      cout<<"*";
    }
    cout<<endl;
  }
}

void pattern7(int n){
  //
  for(int i=0; i<=2*n; i++){
     int start = i;
     if(i>n){
      start = 2*n-i;
     }
     for(int j=0; j<start; j++){
      cout<<"*";
     }
     cout<<endl;
  }
}

void pattern8(int n){
  //
  for(int i=0; i<=n; i++){
      int flip = 0;
      if(i%2==0) flip = 1;
      else flip = 0;
      for(int j=0; j<=i; j++){
        cout<<flip;
        flip = 1-flip;
      }
     cout<<endl;
  }
}

void pattern9(int n){
  for(int i=0; i<=n; i++){
    for(char ch='A'; ch<='A'+i ; ch++){
      cout<<ch;
      
    }
    cout<<endl;
  }
   
}
void pattern10(int n){
  for(int i=0; i<=n; i++){
    for(char ch='A'; ch<='A'+n-i ; ch++){
      cout<<ch;
      
    }
    cout<<endl;
  }
   
}


void pattern11(int n){
  for(int i=0; i<2*n-1; i++){
     for(int j=0; j<2*n-1; j++){
      int top = i;
      int left = j;
      int bottom = (2*n-2 )- i;
      int right =( 2*n-2) - j;
      int mini = min(min(top, bottom), min(left, right));
      cout<<n-mini<<" ";
     }
    cout<<endl;
  }
   
}


int main(){

  //  1. print all stars in a square pattern
  int n;
  cout<<"enter the Number "<<endl;
  cin>>n; 
  // pattern1(n);
  // pattern2(n);
  // pattern3(n);
  // pattern4(n);
  // pattern5(n);
  // pattern6(n);
  // pattern7(n);
  // pattern8(n);
  // pattern9(n);
  // pattern10(n);
  pattern11(n);

  return 0;
};