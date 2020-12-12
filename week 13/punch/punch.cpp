#include<iostream>
#include<vector>
#include<tuple>
#include<limits.h>
#include<algorithm>
#include<utility>

using namespace std; 

int n; 
int k; 
vector<pair<int, int>> bev; 
vector<tuple<int, int, int>> M; 

/*
pair<int, int> algo(int p, int pref){
  if(pref >= k) return{0, 0}; 
  else if(p >= n) return{INT_MAX, INT_MAX}; 
  else if(M[p][pref] != make_pair(-1, -1)) return M[p][pref]; 
  int cnt = 0; 
  pair<int, int> part = {INT_MAX, INT_MAX}; 
  while(true){
    if(algo(p + 1, pref + cnt * bev[p].second).first != INT_MAX){
      bool b = cnt != 0; 
      int cost = cnt * bev[p].first + algo(p + 1, pref + cnt * bev[p].second).first;
      int var = - b + algo(p + 1, pref + cnt * bev[p].second).second;
      part = min(part, {cost, var}); 
    }
    if(cnt * bev[p].second + pref > k) break; 
    cnt++;
  }
  M[p][pref] = part; 
  return part; 
}*/

void testcase(){
  cin >> n >> k; 
  bev.clear(); 
  bev.resize(n); 
  for(int i = 0; i < n; i++){
    int c, v; 
    cin >> c >> v; 
    bev[i] = {c, v}; 
  }
  M.clear(); 
  M.resize(k + 1, make_tuple(INT_MAX, INT_MAX, -1));
  M[0] = make_tuple(0, 0, -1); 
  for(int i = 0; i < n; i++){
    int cost = bev[i].first; 
    int vol = bev[i].second; 
    for(int v = 0; v < k; v++){
      if(get<0>(M[v]) != INT_MAX){
        int nuovo_costo = get<0>(M[v]) + cost; 
        int nuovo_vol = min(v + vol, k); 
        bool diverso = get<2>(M[v]) != i; 
        int nuova_var = get<1>(M[v]) + diverso; 
        if(get<0>(M[nuovo_vol]) > nuovo_costo){
          M[nuovo_vol] = make_tuple(nuovo_costo, nuova_var, i); 
        }
        else if(get<0>(M[nuovo_vol]) == nuovo_costo && get<1>(M[nuovo_vol]) < nuova_var){
          M[nuovo_vol] = make_tuple(nuovo_costo, nuova_var, i); 
        }
      }
    }
  }
  
  cout << get<0>(M[k]) << " " << get<1>(M[k]) << endl; 
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
