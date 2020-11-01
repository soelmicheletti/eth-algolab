#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<limits.h>

using namespace std; 

bool bs(vector<int> &A, int k, int l, int r){
  if(l == r) return A[l] == k; 
  if(r < l) return false; 
  int mid = (l + r) / 2; 
  if(A[mid] == k) return true; 
  if(A[mid] < k) return bs(A, k, mid + 1, r); 
  else return bs(A, k, l, mid - 1); 
}

void testcase(){
  int n, M, S, T; 
  cin >> n >> M >> S >> T; 
  vector<int> montagna(M);
  for(int i = 0; i < M; i++) cin >> montagna[i];
  vector<int> sea(S); 
  for(int i = 0; i < S; i++) cin >> sea[i]; 
  vector<int> begin(T); 
  for(int i = 0; i < T; i++) cin >> begin[i];
  vector<int> end(T);
  for(int i = 0; i < T; i++) cin >> end[i];
  
  sort(montagna.begin(), montagna.end());
  sort(sea.begin(), sea.end());
  
  int best_index = INT_MIN; 
  int best = 0; 
  
  for(int i = 0; i < T; i++){
    vector<int>::iterator l;
    vector<int>::iterator r;
    l = lower_bound(sea.begin(), sea.end(), begin[i]);
    r = lower_bound(sea.begin(), sea.end(), end[i]);
    if(!bs(sea, begin[i], 0, S - 1) && !bs(sea, end[i], 0, S - 1) && r - l == 0){
      l = lower_bound(montagna.begin(), montagna.end(), begin[i]);
      r = lower_bound(montagna.begin(), montagna.end(), end[i]);
      if(r - l > best){
        best = r - l; 
        best_index = i; 
      }
    }
  }
  
  cout << best_index + 1 << endl;
  
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
