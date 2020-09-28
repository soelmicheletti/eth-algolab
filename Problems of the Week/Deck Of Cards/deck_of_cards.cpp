#include<iostream>
#include<vector>
#include<limits.h>

using namespace std; 

void testcase(){
    int n; cin >> n; 
    int k; cin >> k; 
    vector<int> V(n); 
    for(int i = 0; i < n; i++){
        cin >> V[i]; 
    }
    
    vector<int> S(n + 1); 
    S[0] = 0;
    S[1] = V[0];  

    for(int i = 2; i <= n; i++){
        S[i] = S[i - 1] + V[i - 1]; 
    }

    int l = 1; 
    int r = 1; 
    int min = INT_MAX; 
    int left_best = 1; 
    int right_best = 1; 
    bool found = false; 
    while(r <= n){
        if(S[r] - S[l - 1] == k){
            cout << (l - 1) << " " << (r - 1) << endl; 
            found = true; 
            break; 
        } else if(abs(S[r] - S[l - 1] - k) < min){
            min = abs(S[r] - S[l - 1] - k); 
            left_best = l; 
            right_best = r; 
        } 
        
        if(S[r] - S[l - 1] < k){
            r++; 
        }
        else if (S[r] - S[l - 1] > k){
            if(l == r){
              l++; 
              r++; 
            } else{
               l++; 
            }
        }
         
    }

    if(!found){
        cout << (left_best - 1) << " " << (right_best - 1) << endl; 
    }
}

int main(){
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase();
  }
  return 0; 
}
