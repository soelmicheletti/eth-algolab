#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<limits.h>

using namespace std; 

long algo(vector<tuple<long, long>> &M, long s, long T, int n){
  if(n < 0 || T <= 0) return 0; 
  if(get<1>(M[n]) > T){ long res = algo(M, s, T, n - 1); return res;}
  long res = max(get<0>(M[n]) + s + algo(M, s, T - get<1>(M[n]), n - 1), algo(M, s, T, n - 1));
  return res; 
}

void testcase(){
  int n, m; 
  long D, T; 
  cin >> n >> m >> D >> T; 
  vector<tuple<long, long>> M; 
  vector<long> s;
  for(int i = 0; i < n; i++){
    long d, t; 
    cin >> d >> t;
    M.push_back(make_tuple(d, t));
  }
  
  for(int i = 0; i < m; i++){
    long k; cin >> k; 
    s.push_back(k);
  }
  
  
  bool flag = false;
  if(algo(M, 0, T - 1, M.size() - 1) >= D){
    flag = true; 
    cout << 0 << endl; 
  }
  if(!flag){
    for(int i = 0; i < m; i++){
      if(! flag && algo(M, s[i], T - 1, M.size() - 1) >= D){
        cout << i + 1 << endl; 
        flag = true; 
        break;
      }
    }
  }
  if(!flag){
    cout << "Panoramix captured" << endl; 
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  while(t--) testcase(); 
  return 0; 
}
