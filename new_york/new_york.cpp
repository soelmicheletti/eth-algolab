#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<set>
#include<limits.h>

using namespace std; 

void testcase(){
  int n, m, k; 
  cin >> n >> m >> k; 
  vector<int> temp(n); 
  for(int i = 0; i < n; i++) cin >> temp[i]; 
  vector<vector<int>> G(n); 
  vector<int> parent(n); 
  vector<bool> vis(n, false); 
  vector<bool> res(n, false); 
  vector<int> out_degree(n, 0); 
  for(int i = 0; i < n - 1; i++){
    int u, v; 
    cin >> u >> v; 
    parent[v] = u; 
    G[u].push_back(v); 
    parent[v] = u; 
    out_degree[u]++; 
  }
  
  for(int i = 0; i < n; i++){
    if(out_degree[i] > 0) continue; 
    int tail = i; 
    int current = i; 
    int l = 1; 
    
    multiset<int> h; 
    h.insert(temp[current]); 
    while(!vis[tail]){
      int min = *h.begin(); 
      int max = *h.rbegin(); 
      if(abs(max - min) > k){
        vis[tail] = true;
        h.erase(h.find(temp[tail]));
        tail = parent[tail]; 
        l--; 
      }
      else if(l == m){
        res[current] = true; 
        vis[tail] = true; 
        h.erase(h.find(temp[tail])); 
        tail = parent[tail]; 
        l--; 
      }
      else if(parent[current] == current){
        vis[tail] = true; 
        h.clear(); 
      }
      else if(l < m){
        l++; 
        current = parent[current]; 
        h.insert(temp[current]); 
      }
    }
  }
  
  bool flag = false;
  for(int i = 0; i < n; i++){
    if(res[i]){
      cout << i << " ";
      flag = true; 
    }
  }
  
  if(flag) cout << endl; 
  else cout << "Abort mission" << endl; 
  
  
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
