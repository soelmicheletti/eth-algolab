#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

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

std::ostream& operator<<(std::ostream& o, const Edge& e) {
  return o << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e);
}

int n; 
long r; 
vector<pair<P, int>> planets;

int algo(int k){
  Delaunay t; 
  t.insert(planets.begin() + k, planets.end()); 
  vector<vector<int>> G(n); 
  EdgeV edges;
  edges.reserve(3*n); 
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    if(t.segment(e).squared_length() <= CGAL::square(r)){
      G[i1].push_back(i2); 
      G[i2].push_back(i1); 
    }
  }
  
  vector<int> vis(n, false); 
  for(int i = k; i < n; i++){
    if(vis[i]) continue; 
    stack<int> S; 
    S.push(i); 
    int size = 0; 
    while(!S.empty()){
      int u = S.top(); S.pop(); 
      if(!vis[u]) size++; 
      vis[u] = true; 
      for(int j = 0; j < G[u].size(); j++){
        int v = G[u][j]; 
        if(!vis[v]) S.push(v);
      }
    }
    if(size >= k) return k; 
  }
  return -1; 
}

void testcase(){
  cin >> n >> r; 
  planets.clear(); 
  planets.resize(n); 
  for(int i = 0; i < n; i++){
    int x, y; 
    cin >> x >> y; 
    planets[i] = {P(x,y), i}; 
  }
  int res = INT_MIN; 
  int l = 0; 
  int r = n - 1; 
  while(l <= r){
    int m = (l + r) / 2; 
    if(algo(m) == -1) r = m - 1; 
    else{
      res = max(res, m); 
      l = m + 1; 
    }
  }
  cout << res << endl; 
}

int main(){
  ios_base::sync_with_stdio(false);
  cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0;
}
