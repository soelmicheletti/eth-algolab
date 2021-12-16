#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std; 

int algo(const vector<int> &S, vector<vector<int>> & M, int beg, int end){
  if(end - beg == 0){
    M[beg][end] = S[beg];
    return S[beg];
  }
  if(end - beg == 1){
    M[beg][end] = max(S[beg], S[end]);
    return max(S[beg], S[end]);
  }
  if(end - beg == 2){
    int first = S[beg] + min(S[beg + 1], S[beg + 2]);
    int second = S[end] + min(S[beg], S[beg + 1]);
    M[beg][end] = max(first, second);
    return max(first, second);
  }
  if(M[beg][end] != -1) return M[beg][end];
  else{
    int first = S[beg] + min(algo(S, M, beg + 2, end), algo(S, M, beg + 1, end - 1));
    int second = S[end] + min(algo(S, M, beg + 1, end - 1), algo(S, M, beg, end - 2)); 
    M[beg][end] = max(first, second); 
    return max(first, second);
  }
}

void testcase(){
  int n; cin >> n; 
  vector<int> S(n); 
  for(int i = 0; i < n; i++){
    int k; cin >> k; 
    S[i] = k; 
  }
  
  vector<vector<int>> M(n);
  for(int i = 0; i < n; i++){
    vector<int> k(n); 
    M[i] = k; 
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      M[i][j] = -1;
    }
  }
  
  cout << algo(S, M, 0, S.size() - 1) << endl; 
  
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
