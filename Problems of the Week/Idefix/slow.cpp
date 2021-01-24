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

std::ostream& operator<<(std::ostream& o, const Edge& e) {
  return o << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e);
}
int n, m, k;
long s; 
vector<long> dist; 

int algo(vector<vector<pair<int, long>>> &G, vector<P> &bones, Delaunay &t, long par){
  vector<int> comp(n, 0); 
  vector<bool> vis(n, false); 
  int cmp = -1; 
  for(int i = 0; i < n; i++){
    if(vis[i]) continue; 
    cmp++; 
    stack<int> S; 
    S.push(i); 
    while(!S.empty()){
      int u = S.top(); S.pop(); 
      vis[u] = true; 
      comp[u] = cmp; 
      for(int p = 0; p < G[u].size(); p++){
        int v = G[u][p].first; 
        long w = G[u][p].second; 
        if(!vis[v] && w <= par) S.push(v); 
      }
    }
  }
  
 /* for(int i = 0; i < n; i++) cout << comp[i] << " ";
  cout << endl; */
  vector<int> res(n, 0); 
  for(int i = 0; i < bones.size(); i++){
    auto v = t.nearest_vertex(bones[i]); 
    if(4 * CGAL::squared_distance(v -> point(), bones[i]) > par) continue;
    //cout << "info " << v -> info() << " component " << comp[v -> info()] << endl; 
    res[comp[v -> info()]]++; 
  }
  
  int massimo = INT_MIN; 
  for(int i = 0; i < n; i++){
    massimo = max(massimo, res[i]); 
  }
  return massimo; 
}

void testcase(){
  cin >> n >> m >> s >> k; 
  
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  Delaunay t;
  t.insert(points.begin(), points.end());
  EdgeV edges;
  edges.reserve(3*n); // there can be no more in a planar graph
  vector<long> cand;
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
    //cand.push_back(t.segment(e).squared_length()); 
  }
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });

  vector<vector<pair<int, long>>> G(n); 
  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      G[get<0>(*e)].push_back({get<1>(*e), get<2>(*e)});
      G[get<1>(*e)].push_back({get<0>(*e), get<2>(*e)});
      cand.push_back(get<2>(*e)); 
      uf.link(c1, c2);
      if (--n_components == 1) break;
    }
  }
  dist.clear(); dist.resize(m, 0); 
  vector<P> bones; 
  for(int i = 0; i < m; i++){
    int x, y; cin >> x >> y; 
    bones.push_back(P(x, y)); 
    dist[i] = CGAL::squared_distance(P(x, y), t.nearest_vertex(P(x, y)) -> point()); 
    cand.push_back(CGAL::squared_distance(P(x, y), t.nearest_vertex(P(x, y)) -> point()) * 4);
  }
  
  cout << algo(G, bones, t, s) << " "; 
  /*for(int i = 0; i < n; i++){
    for(int j = 0; j < G[i].size(); j++) cout << "From " << i << " to " << G[i][j].first << " length " << G[i][j].second << endl; 
  }*/
  sort(cand.begin(), cand.end()); 
  int l = 0; 
  int r = cand.size() - 1; 
  while(l <= r){
    int m = (l + r) / 2; 
    if(algo(G, bones, t, cand[m]) < k) l = m + 1; 
    else if(m > 0 && algo(G, bones, t, cand[m - 1]) < k){
      cout << cand[m] << endl; return; 
    }
    else if(m == cand.size() - 1){
      cout << cand[m] << endl; 
      return; 
    }
    else if(m == 0){
      cout << cand[0] << endl; return; 
    }
    else r = m - 1; 
  }
}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0;
}
