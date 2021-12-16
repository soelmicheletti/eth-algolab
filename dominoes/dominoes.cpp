#include<iostream>

using namespace std;

void testcase(){
  
  int n; cin >> n; 
  int h[n]; 
  for(int i = 0; i < n; i++){
    int k; cin >> k; 
    h[i] = k; 
  }
  
  int max = 0; 
  
  for(int i = 0; i < n; i++){
    if(i <= max && i + h[i] - 1 > max){
      max = i + h[i] - 1; 
    }
  }
  if(max > n){
    max = n - 1; 
  }
  cout << max + 1 << '\n';
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase();
  }
  return 0; 
}
