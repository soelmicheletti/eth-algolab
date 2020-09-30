#include<iostream>

using namespace std; 

void testcase(){
  int n; cin >> n; 
  int A[n][n];
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      int k; cin >> k; 
      A[i][j] = k; 
    }
  }
  
  int S[n+1][n];
  for(int i = 0; i < n + 1; i++){
    for(int j = 0; j < n; j++){
      S[i][j] = 0; 
    }
  }
  
  for(int i = 1; i < n + 1; i++){
    for(int j = 0; j < n; j++){
      S[i][j] = S[i - 1][j] + A[i - 1][j];
    }
  }
  
  int res = 0; 
  
  for(int i = 0; i < n; i++){
    for(int j = i; j < n; j++){
      
      int tmp[n];
      
      for(int a = 0; a < n; a++){
        tmp[a] = S[j+1][a] - S[i][a];
      }
      
      int even = 0;
      int odd = 0; 
      int sum = 0; 
      for(int l = 0; l < n; l++){
        sum += tmp[l];
        if(sum % 2 == 0) even++; 
        else odd++;
      }
      
      res += (even * (even - 1) / 2) + (odd * (odd - 1) / 2) + even; 
      
    }
  }
  
  cout << res << '\n';
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
