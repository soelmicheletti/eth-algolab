#include<iostream>
#include<vector>
#include<limits.h>
#include<algorithm>
#include<utility>
#include<set>

using namespace std; 

void testcase(){
  int n, m; 
  cin >> n >> m; 
  vector<int> friends(n); 
  multiset<int> h; 
  multiset<int> boxes; 
  for(int i = 0; i < n; i++){
   int k; cin >> k; 
   friends[i] = k; 
   h.insert(k); 
  } 
  bool flag = false; 
  for(int i = 0; i < m; i++){
    int k; cin >> k;
    auto v = h.end(); v--; 
    if(k > *v) flag = true; 
    boxes.insert(-k); 
  } 
  sort(friends.begin(), friends.end()); 
  if(flag) cout << "impossible" << endl; 
  else{
    int r = 0; 
    while(!boxes.empty()){
      for(int i = n - 1; i >= 0; i--){
        auto v = boxes.end(); v--; 
        if(-friends[i] <= *v){
          boxes.erase(boxes.find(*boxes.lower_bound(-friends[i]))); 
          if(boxes.empty()) break; 
        }
        else break; 
      }
      r++; 
    }
    cout << 3 * (r - 1) + 2 << endl; 
  }
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
