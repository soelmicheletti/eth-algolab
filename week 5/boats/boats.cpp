#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>
#include<limits.h>

using namespace std; 

void testcase(){
  int n; cin >> n; 
  vector<tuple<int, int>> B(n); 
  for(int i = 0; i < n; i++){
    int l, p; 
    cin >> l >> p; 
    B[i] = make_tuple(p, l); 
  }
  
  sort(B.begin(), B.end()); 
  
  int res = 1; 
  int last = get<0>(B[0]);
  int i = 1; 
  
  while(i < n){
    int chosen_j = -1;
    int best = INT_MAX;
    for(int j = i; j < n; j++){
      if(get<0>(B[j]) >= best) j = n;
      else if(get<0>(B[j]) >= last && max(last + get<1>(B[j]), get<0>(B[j])) < best){
        best = max(last + get<1>(B[j]), get<0>(B[j]));
        chosen_j = j; 
      }
    }
    if(chosen_j != -1){
      last = best; 
      res++;
      i = chosen_j + 1; 
    }
    else{
      i = n; 
    }
  }
  
  cout << res << endl;
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
