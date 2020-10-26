#include<iostream>
#include<vector>
#include<tuple>
#include<limits.h>
#include<algorithm>

using namespace std; 

int n; 

int unlock(vector<bool> &unlocked, int p, int t){
  if(unlocked[p]) return 0;
  if(p >= (n - 1) / 2){
    unlocked[p] = true; 
    return 1;
  }  
  if(2 * p + 1 > n){
    unlocked[p] = true; 
    t++; 
    return t; 
  }
  if(2 * p + 2 > n){
    int tmp = unlock(unlocked, 2 * p + 1, 0);
    unlocked[p] = true; 
    return tmp + 1; 
  }
  else{
    int tmp = unlock(unlocked, 2 * p + 1, 0) + unlock(unlocked, 2 * p + 2, 0);
    unlocked[p] = true; 
    return tmp + 1; 
  }
}

void testcase(){
  cin >> n; 
  vector<tuple<int, int>> T(n);
  vector<bool> unlocked(n, false);
  for(int i = 0; i < n; i++){
    int k; cin >> k; 
    T[i] = make_tuple(k, i); 
  }
  sort(T.begin(), T.end());
  int t = 0; 
  bool res = true; 
  for(int i = 0; i < n; i++){
    if(!unlocked[get<1>(T[i])]){
      t += unlock(unlocked, get<1>(T[i]), t);
      //cout << "for index " << get<1>(T[i]) << " t = " << t << endl; 
      if(t > get<0>(T[i])){
        res = false; 
      }
    }
  }
  
  if(res){
    cout << "yes" << endl; 
  }
  else{
    cout << "no" << endl; 
  }
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
