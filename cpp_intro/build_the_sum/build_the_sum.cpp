#include<iostream>

using namespace std; 

void testcase(){
  int n; cin >> n; 
  int sum = 0; 
  for(int i = 0; i < n; i++){
    int k; cin >> k; 
    sum += k; 
  }
  cout << sum << endl; 
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
