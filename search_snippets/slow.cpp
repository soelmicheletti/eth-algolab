#include<iostream>
#include<vector>
#include<limits.h>

using namespace std;

void testcase(){
  int n; cin >> n; 
  vector<vector<int>> S(n); 
  vector<int> lunghezza(n); 
  for(int i = 0; i < n; i++){
    int k; cin >> k; 
    vector<int> nuovo(k); 
    S[i] = nuovo; 
    lunghezza[i] = k; 
  }
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < lunghezza[i]; j++){
      int k; cin >> k; 
      S[i][j] = k; 
    }
  }
  vector<int> p(n); 
  for(int i = 0; i < n; i++){
    p[i] = 0; 
  }
  int min = INT_MAX; 
  
  vector<int> min_pointer(2);
  min_pointer[0] = 0; min_pointer[1] = 0; 
  int tmp = INT_MAX; 
  for(int i = 0; i < n; i++){
    if(S[i][0] < tmp){
      min_pointer[0] = i; 
      tmp = S[i][0]; 
    }
  }
  
  vector<int> max_pointer(2); 
  max_pointer[0] = 0; max_pointer[1] = 0; 
  tmp = INT_MIN; 
  for(int i = 0; i < n; i++){
    if(S[i][0] > tmp){
      max_pointer[0] = i; 
      tmp = S[i][0]; 
    }
  }
  
  
  
  while(min_pointer[1] < lunghezza[min_pointer[0]]){
    int now = S[max_pointer[0]][max_pointer[1]] - S[min_pointer[0]][min_pointer[1]] + 1; 
    if(now < min){
      min = now; 
    }
    p[min_pointer[0]]++; 
    min_pointer[1]++; 
    tmp = INT_MAX;
    for(int i = 0; i < n; i++){
        if(S[i][p[i]] < tmp){
            min_pointer[0] = i;
            min_pointer[1] = p[i];
            tmp = S[i][p[i]]; 
        }
    }
    tmp = INT_MIN;
    for(int i = 0; i < n; i++){
      if(S[i][p[i]] > tmp){
          max_pointer[0] = i;
          max_pointer[1] = p[i];
          tmp = S[i][p[i]]; 
      }
    }
  }
  
  cout << min << endl;
  
}



int main(){
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
