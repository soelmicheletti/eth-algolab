#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K:: Point_2 P; 
typedef K:: Line_2 L; 
typedef K:: Segment_2 S; 

using namespace std; 

void testcase(int n){
  long x, y, a, b; 
  cin >> x >> y >> a >> b; 
  K:: Ray_2 ray(P(x, y), P(a, b)); 
  vector<S> segm(n); 
  for(int i = 0; i < n; i++){
    long s1, e1, s2, e2; 
    cin >> s1 >> e1 >> s2 >> e2; 
    S s(P(s1, e1), P(s2, e2));
    segm[i] = s;
  }
  
  bool flag = false; 
  for(int i = 0; i < n; i++){
    if(!flag && do_intersect(segm[i], ray)){
      flag = true; 
    }
  }
  
  if(flag) cout << "yes" << "\n";
  else cout << "no" << "\n";
  
}

int main(){
  ios_base::sync_with_stdio(false);
  bool flag = true; 
  while(flag){
    int n; cin >> n; 
    if(n == 0){
      flag = false; 
      break; 
    }
    else{
      testcase(n); 
    }
  }
  return 0; 
}
