#include<iostream>

using namespace std; 

void testcase(){
  int n; cin >> n; 
  int S[n]; 
  for(int i = 0; i < n; i++){
    int k; cin >> k; 
    S[i] = k; 
  }
  int even = 0; 
  int odd = 0; 
  int sum = 0; 
  
  for(int i = 0; i < n; i++){
    sum += S[i]; 
    if(sum % 2 == 0) even++; 
    else odd++; 
  }
  int result = (even * (even - 1) / 2) + (odd * (odd - 1) / 2) + even; 
  cout << result << endl; 
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
