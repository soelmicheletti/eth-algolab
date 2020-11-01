#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>

using namespace std; 

int mS(vector<int> &A, int l, int r){
  if(r - l == 1) return 0; 
  int mid = (l + r) / 2; 
  int res = 0; 
  res += mS(A, l, mid); 
  res += mS(A, mid, r); 
  vector<int> tmp(r - l); 
  int left = l; 
  int right = mid; 
  int i = 0; 
  while(left < mid && right < r){
    if(A[left] <= A[right]){
      tmp[i] = A[left]; 
      i++; 
      left++; 
    }
    else{
      tmp[i] = A[right];
     // cout << A[left] << " " << A[right] << endl; 
      i++; right++;  res += (mid - left);
    }
  }
  
  while(left < mid){tmp[i] = A[left]; i++; left++; }
  while(right < r){tmp[i] = A[right]; i++; right++; }
  i = 0;
  for(int j = l; j < r; j++){
    A[j] = tmp[i];
    i++;
  }
  
  return res; 
}

void testcase(){
  int n; cin >> n; 
  vector<int> A(n); 
  for(int i = 0; i < n; i++){
    cin >> A[i]; 
  }
  int res = mS(A, 0, n); 
  cout << res << endl; 
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
