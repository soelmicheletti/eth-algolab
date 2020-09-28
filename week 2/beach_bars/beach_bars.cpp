#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<limits.h>

using namespace std; 

void testcase(){
  int n; cin >> n; 
  vector<int> S(n); 
  for(int i = 0; i < n; i++){
    int k; cin >> k; 
    S[i] = k; 
  }
  sort(S.begin(), S.end()); 
  
  int l = 0; 
  int r = 0; 
  int nmb = 0; 
  int dist = INT_MAX; 
  vector<int> pos; 
  
  while(r < n - 1 && l < n - 1){
  //  cout << l << " " << r << endl; 
    while(r < n - 1 && S[r] - S[l] < 200) r++; 
    if(S[r] - S[l] > 200) r--; 
    int ombrelloni = r - l + 1; 
    int distanza = 0; 
    bool pari = (S[r] + S[l]) % 2 == 0; 
    if(pari) distanza = (S[r] - S[l]) / 2; 
    else{
      distanza = (S[r] - S[l] + 1) / 2;
    }
    
    if(ombrelloni > nmb){
      nmb = ombrelloni; 
      dist = distanza; 
      pos.clear(); 
      if(pari) pos.push_back((S[r] + S[l]) / 2);
      else{
        pos.push_back((S[r] + S[l] - 1) / 2); 
        pos.push_back((S[r] + S[l] + 1) / 2);
      }
    }
    else if(ombrelloni == nmb && distanza < dist){
      nmb = ombrelloni; 
      dist = distanza; 
      pos.clear(); 
      if(pari) pos.push_back((S[r] + S[l]) / 2);
      else{
        pos.push_back((S[r] + S[l] - 1) / 2); 
        pos.push_back((S[r] + S[l] + 1) / 2);
      }
    }
    else if(ombrelloni == nmb && distanza == dist){
      if(pari) pos.push_back((S[r] + S[l]) / 2);
      else{
        pos.push_back((S[r] + S[l] - 1) / 2); 
        pos.push_back((S[r] + S[l] + 1) / 2);
      }
    }
    l++;
  }
  
  cout << nmb << " " << dist << endl; 
  for(int i = 0; i < pos.size(); i++){
    cout << pos[i] << " "; 
  }
  cout << endl; 
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
