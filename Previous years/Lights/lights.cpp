#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include<limits.h>

using namespace std; 

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef K::Point_2 P; 

struct person{
  P p; 
  long r;
};

void testcase(){
  int m, n; cin >> m >> n; 
  vector<person> A; 
  for(int i = 0; i < m; i++){
    P p; cin >> p; 
    long r; cin >> r; 
    A.push_back({p, r}); 
  }
  
  long h; cin >> h; 
  vector<P> light; 
  for(int i = 0; i < n; i++){
    P p; cin >> p; 
    light.push_back(p); 
  }
  
  Delaunay t; 
  t.insert(light.begin(), light.end()); 
  
  vector<int> res(m, -1); 
  bool flag = false; 
  int last = 0; 
  for(int i = 0; i < m; i++){
    P p = A[i].p; 
    int r = A[i].r; 
    auto v = t.nearest_vertex(p); 
    if(CGAL::squared_distance(p, v-> point()) >= CGAL::square(r + h)){flag = true;}
    else if(flag){res[i] = 0; continue;} 
    else{
      for(int j = 0; j < n; j++){
        if(CGAL::squared_distance(p, light[j]) < CGAL::square(r + h)){
          res[i] = j; last = max(last, j); 
          break;
        }
      }
    }
  }
  
  for(int i = 0; i < m; i++){
    if(flag && res[i] == -1) cout << i << " ";
    else if(!flag && res[i] == last) cout << i << " ";
  }
  cout << endl;   
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0;
}
