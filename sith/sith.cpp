#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include<stack>

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

/*void compute_emst() {
  Index n;
  std::cin >> n;

  // read points: first, we read all points and store them into a vector,
  // together with their indices
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  for (Index i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  // then we build the Delaunay triangulation in one shot, so as to leave the
  // choice of an efficient insertion order to the triangulation structure. By
  // giving the points paired with the indices, these indices are used to
  // initialize the vertex info accordingly.
  // This step takes O(n log n) time (for constructing the triangulation).
  Delaunay t;
  t.insert(points.begin(), points.end());

  // extract edges and sort by (squared) length
  // This step takes O(n log n) time (for the sorting).
  EdgeV edges;
  edges.reserve(3*n); // there can be no more in a planar graph
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    // ensure smaller index comes first
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });

  // Compute EMST using Kruskal's algorithm. This step takes O(n alpha(n)) time
  // in theory; for all practical purposes alpha(n) is constant, so linear time.

  // setup and initialize union-find data structure
  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;
  // ... and process edges in order of increasing length
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    // determine components of endpoints
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      // this edge connects two different components => part of the emst
      uf.link(c1, c2);
      std::cout << *e << "\n";
      if (--n_components == 1) break;
    }
  }
}*/


int n; 
long r; 
typedef K::Point_2 P; 
typedef std::pair<P,Index> IPoint;
vector<IPoint> points;
vector<vector<int>> G;

bool algo(int m){
  Delaunay t; 
  t.insert(points.begin() + m, points.end()); 
  
  G.clear(); G.resize(n); 
  EdgeV edges;
  edges.reserve(3*n); // there can be no more in a planar graph
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    if(t.segment(e).squared_length() <= CGAL::square(r)){
      G[i1].push_back(i2); 
      G[i2].push_back(i1); 
    }
  }
  vector<bool> vis(n, false); 
  for(int i = 0; i < n; i++){
    if(vis[i]) continue; 
    stack<int> S; 
    int size = 0; 
    S.push(i); 
    while(!S.empty()){
      int u = S.top(); S.pop(); 
      if(!vis[u]){
        vis[u] = true; 
        size++; 
      }
      for(int j = 0; j < G[u].size(); j++){
        int v = G[u][j]; 
        if(!vis[v]) S.push(v); 
      }
    }
    if(size >= m) return true; 
  }
  return false; 
  
}

void testcase(){
  cin >> n >> r; 
  points.clear(); points.resize(n);   
  points.reserve(n);
  for(int i = 0; i < n; i++){
    int x, y; cin >> x >> y; 
    points[i] = {P(x, y), i}; 
  }
  
  int l = 0; 
  int r = n / 2; 
  while(l <= r){
    int m = (l + r) / 2; 
    if(!algo(m)) r = m - 1; 
    else if(m == n - 1){
      cout << m << endl; 
      break; 
    }
    else if(!algo(m + 1)){
      cout << m << endl; 
      return; 
    }
    else l = m + 1; 
  }
  

}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0;
}
