#include<iostream>
#include<vector>
#include<algorithm>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;


using namespace std; 

struct biker{
    K::FT yStart;
    K::Sign sign;
    K::FT slope;
    int index;
};

bool cmp(biker &a, biker &b){
  if(a.yStart <= b.yStart) return 0; 
  return 1; 
}

bool cmpI(biker &a, biker &b){
  if(a.index <= b.index) return 1; 
  return 0; 
}

void testcase(){
  int n; cin >> n; 
  vector<biker> S(n); 
  
  for(int i = 0; i < n; i++){
    long y0, x1, y1;
    cin >> y0 >> x1 >> y1; 
    auto p1 = P(0, y0);
    auto p2 = P(x1, y1);
    auto slope = (p2.y() - p1.y()) / p2.x();
    K::Sign sign = CGAL::sign(slope);
    auto absSlope = CGAL::abs(slope);
    biker b = {y0, sign, absSlope, i};
    S[i] = b; 
  }
  
  sort(S.begin(), S.end(), cmp);
  
  vector<biker> res; 
  
  for(int i = 0; i < n; i++){
    biker curr = S[i]; 
    
    if(curr.sign == CGAL::NEGATIVE){
      if(res.empty() || curr.sign * curr.slope <= res.back().sign * res.back().slope){
        res.push_back(curr); 
      }
      else{
        int j = res.size() - 1; 
        while(j >= 0 && curr.sign * curr.slope > res[j].sign * res[j].slope){
          res.erase(res.begin() + j);
          j--;
        }
        res.push_back(curr); 
      }
    }
    else{
      if(res.empty() || curr.slope <= res.back().sign * res.back().slope){
        res.push_back(curr); 
      }
      else{
        bool add = true; 
        for (int j = res.size() - 1; j >= 0; j--){
          biker prev = res[j];
          if (curr.slope > prev.slope){
            add = false;
            break; 
          }
          else if (curr.slope <= prev.slope * prev.sign){
            break;
          }
          else{ 
            res.erase(res.begin() + j);
          }
        }
        if (add){
          res.push_back(curr);
        }
      }
    }
  }
  
  sort(res.begin(), res.end(), cmpI);
  
  for(int i = 0; i < res.size(); i++){
    cout << res[i].index << " ";
  }
  cout << endl; 
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
