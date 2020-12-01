#include<iostream>
#include<vector>

using namespace std; 

void testcase(){
  int n, k, w; 
  cin >> n >> k >> w; 
  vector<int> c(n); 
  for(int i = 0; i < n; i++){
    int k; cin >> k;
    c[i] = k; 
  }
  
  vector<vector<int>> G(w); 
  vector<vector<int>> P(w); 
  for(int i = 0; i < w; i++){
    int l; cin >> l; 
    G[i] = vector<int>(l, 0); 
    for(int j = 0; j < l; j++){
      int k; cin >> k; 
      G[i][l - 1 - j] = c[k]; 
      if(k != 0) P[i].push_back(c[k]); 
    }
  }
  
  int best = 0; 
  vector<pair<int, int>> S(k, {0, -1});
  vector<pair<int, int>> SS(k, {0, -1});
  for(int i = 0; i < w; i++){
    int l = 0;
    int r = 0; 
    int sum = G[i][0]; 
    int size = 1; 
    while(r < G[i].size()){
      if(sum == k){
        best = max(best, size); 
        r++; 
        if(r < G[i].size()){sum += G[i][r]; size++;}
      }
      else if(sum < k){
        r++; 
        if(r < G[i].size()){sum += G[i][r]; size++; }
      }
      else if(sum > k){
        sum -= G[i][l]; 
        l++; 
        if(l < r){size--;}
        if(l == r){size = 1;}
        if(l > r){r = l; sum = G[i][l]; size = 1;}
      }
    }
  }
  
  for(int i = 0; i < w; i++){
    int part = 0;
    int size = 0;
    for(int j = 0; j < P[i].size(); j++){
      part += P[i][j];
      if(part > k - c[0]) j = P[i].size();
      else{size++;
      if(S[part].second != i && S[part].first < size){
        S[part] = {size, i};
      }
      else if(SS[part].first < size){
        SS[part] = {size, i};
      }
      }
    }
  }
  
  for(int i = 1; i < k; i++){
    if(k - i - c[0] >= 0){
    int i1, s1, i2, s2, i3, s3, i4, s4;
    i1 = S[i].second; s1 = S[i].first;
    i2 = SS[i].second; s2 = SS[i].first;
    i3 = S[k - i - c[0]].second; s3 = S[k - i - c[0]].first; 
    i4 = SS[k - i - c[0]].second; s4 = SS[k - i - c[0]].first;
    if(i1 != i3 && i1 != -1 && i3 != -1) best = max(best, s1 + s3 + 1);
    if(i1 != i4 && i1 != -1 && i4 != -1) best = max(best, s1 + s4 + 1);
    if(i2 != i3 && i2 != -1 && i3 != -1) best = max(best, s2 + s3 + 1);
    if(i2 != i4 && i2 != -1 && i4 != -1) best = max(best, s2 + s4 + 1); 
    }
  }
  
  cout << best << endl; 
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
