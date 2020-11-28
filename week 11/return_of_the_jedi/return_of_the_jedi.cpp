#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<algorithm>
#include<utility>
#include<tuple>
#include<limits.h>

using namespace std; 

struct cmp{
bool operator()(tuple<int, int, int> a, tuple<int, int, int> b){
  if(get<0>(a) < get<0>(b)) return !true; 
  else if(get<0>(a) > get<0>(b)) return !false; 
  else if(get<1>(a) < get<1>(b)) return !false; 
  else if(get<1>(a) > get<1>(b)) return !true; 
  else if(get<2>(a) < get<2>(b)) return !false; 
  else if(get<2>(a) > get<2>(b)) return !false; 
}
};

void testcase(){
  int n, s; 
  cin >> n >> s; 
  vector<vector<int>> G(n, vector<int>(n, 0)); 
  vector<vector<bool>> B(n, vector<bool>(n, false));
  for(int i = 1; i <= n - 1; i++){
    for(int j = i; j < n; j++){
      int k; cin >> k; 
      G[i-1][j] = k; 
      G[j][i - 1] = k; 
    }
  }
  
  set<int> S; 
  S.insert(s - 1); 
  priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, cmp> Q; 
  for(int i = 0; i < n; i++){
    if(G[s - 1][i] != 0){
      Q.push(make_tuple(G[s - 1][i], i, s - 1)); 
    }
  }
  int cost = 0; 
  vector<vector<pair<int, int>>> T(n);
  while(!Q.empty()){
    tuple<int, int, int> e = Q.top(); Q.pop(); 
    int w = get<0>(e); 
    int v = get<1>(e); 
    int u = get<2>(e); 
    if(S.find(u) != S.end() && S.find(v) == S.end()){
      cost += w; 
      S.insert(v); 
      B[u][v] = true;
      T[u].push_back(make_pair(v, w));
      T[v].push_back(make_pair(u, w)); 
      for(int i = 0; i < n; i++){
        if(i != v && S.find(i) == S.end()){
          Q.push(make_tuple(G[v][i], i, v)); 
        }
      }
    }
  }
  
  vector<vector<int>> DP(n, vector<int>(n, INT_MIN));
  for(int i = 0; i < n; i++){
    stack<int> S; 
    S.push(i);
    vector<bool> visited(n, false);
    while(!S.empty()){
      int u = S.top(); S.pop(); 
      visited[u] = true; 
      for(int j = 0; j < T[u].size(); j++){
        int v = T[u][j].first; 
        int w = T[u][j].second; 
        if(!visited[v]){
          DP[i][v] = max(DP[i][u], w); 
          S.push(v); 
        }
      }
    }
  }

  int res = INT_MAX;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(!B[i][j] && !B[j][i] && G[i][j] != 0){
        int nuovo = cost - max(DP[i][j], DP[j][i]) + G[i][j];
        res = min(res, nuovo);
      }
    }
  }
  
  cout << res << endl;
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
