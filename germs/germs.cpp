#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<utility>
#include<limits.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

using namespace std; 

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;


std::ostream& operator<<(std::ostream& o, const Edge& e) {
  return o << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e);
}

void testcase(int n){
  int l, b, r, u; 
  cin >> l >> b >> r >> u; 
  // Time needed for point i to hit a boundary
  vector<double> boundary(n); 
  // Time needed for point i to hit another germ
  vector<double> germ(n, INT_MAX); 
  // Time before point i dies
  vector<double> tempo(n); 
  
  
  typedef pair<K::Point_2, Index> IPoint;
  vector<IPoint> points;
  points.reserve(n);
  for (Index i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    double res = (u - y) - 0.5;
    res = min(res, (y - b) - 0.5); 
    res = min(res, (x - l) - 0.5);
    res = min(res, (r - x) - 0.5); 
    boundary[i] = res; 
    points.emplace_back(K::Point_2(x, y), i);
  }

  Delaunay t;
  t.insert(points.begin(), points.end());

  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2);
    germ[i1] = min(germ[i1], (CGAL::sqrt(t.segment(e).squared_length()) - 1) * 0.5);
    germ[i2] = min(germ[i2], (CGAL::sqrt(t.segment(e).squared_length()) - 1) * 0.5);
  }
  
  for(int i = 0; i < n; i++){
    tempo[i] = min(boundary[i], germ[i]);
  }
  sort(tempo.begin(), tempo.end());
  cout << ceil(CGAL::sqrt(tempo[0])) << " " << ceil(CGAL::sqrt(tempo[n / 2])) << " " << ceil(CGAL::sqrt(tempo[n - 1])) << endl; 
  
}

int main(){
  ios_base::sync_with_stdio(false); 
  while(true){
    int n; cin >> n; 
    if(n == 0) break; 
    testcase(n); 
  }
  return 0; 
}
