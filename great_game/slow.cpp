#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<limits.h>

using namespace std; 

bool contains(const vector<int> &t, int n){
  for(int i = 0; i < t.size(); i++){
    if(t[i] == n) return true; 
  }
  return false; 
}

int algo(vector<vector<int>> & uno, vector<vector<int>> & due, vector<vector<int>> & tre, vector<vector<int>> & quattro, const vector<vector<int>> &trans, int r, int b, int evenS, int evenM, int turn, int n){
  if(r == n) return 0; 
  if(b == n) return 1; 
  if(turn == 0 && evenS == 0){
    if(uno[r][b] != -1) return uno[r][b]; 
    else{
      for(int i = 0; i < trans[r].size(); i++){
        if(algo(uno, due, tre, quattro, trans, trans[r][i], b, 1, evenM, 1, n) == 0){uno[r][b] = 0; return 0;}
      }
      uno[r][b] = 1;
      return 1; 
    }
  }
  else if(turn == 0 && evenS == 1){
    if(due[r][b] != -1) return due[r][b];
    for(int i = 0; i < trans[b].size(); i++){
      if(algo(uno, due, tre, quattro, trans, r, trans[b][i], 0, evenM, 1, n) == 0){due[r][b] = 0; return 0;} 
    }
    due[r][b] = 1; 
    return 1; 
  }
  else if(turn == 1 && evenM == 0){
    if(tre[r][b] != -1) return tre[r][b];
    else{
      for(int i = 0; i < trans[b].size(); i++){
        if(algo(uno, due, tre, quattro, trans, r, trans[b][i], evenS, 1, 0, n) == 1){tre[r][b] = 1; return 1;} 
      }
      tre[r][b] = 0;
      return 0; 
    }
  }
  else if(turn == 1 && evenM == 1){
      if(quattro[r][b] != -1) return quattro[r][b];
      for(int i = 0; i < trans[r].size(); i++){
        if(algo(uno, due, tre, quattro, trans, trans[r][i], b, evenS, 0, 0, n) == 1){quattro[r][b] = 1; return 1;} 
      }
      quattro[r][b] = 0; 
      return 0; 
  }
}

void testcase(){
  int n; cin >> n; 
  int m; cin >> m; 
  vector<vector<int>> trans(n); 
  for(int i = 0; i < n; i++){
    vector<int> k; 
    trans[i] = k; 
  }
  int r; cin >> r; 
  int b; cin >> b; 
  for(int i = 0; i < m; i++){
    int u; cin >> u; 
    int v; cin >> v; 
    trans[u].push_back(v); 
  }
  
  vector<vector<int>> uno(n);
  for(int i = 0; i < n; i++){
    vector<int> k(n);
    uno[i] = k;
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      uno[i][j] = -1;
    }
  }
  
  vector<vector<int>> due(n);
  for(int i = 0; i < n; i++){
    vector<int> k(n);
    due[i] = k;
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      due[i][j] = -1;
    }
  }
  
  vector<vector<int>> tre(n);
  for(int i = 0; i < n; i++){
    vector<int> k(n);
    tre[i] = k;
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      tre[i][j] = -1;
    }
  }
  
  vector<vector<int>> quattro(n);
  for(int i = 0; i < n; i++){
    vector<int> k(n);
    quattro[i] = k;
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      quattro[i][j] = -1;
    }
  }
  
  cout << algo(uno, due, tre, quattro, trans, r, b, 0, 0, 0, n) << endl; 
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase();
  }
  return 0; 
}
