#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include<queue>
#include <algorithm>
#include <iostream>

using namespace std; 

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef K::Point_2 P; 

int k; 
int algo(vector<vector<pair<int, long>>> &G, long s, int n){
  vector<bool> vis(n, false); 
  vector<int> conn_components; 
  
  for(int i = 0; i < n; i++){
    if(vis[i]) continue; 
    int size = 0; 
    queue<int> Q; 
    Q.push(i); 
    while(!Q.empty()){
      int u = Q.front(); Q.pop();
      vis[u] = true; 
      size++; 
      for(int i = 0; i < G[u].size(); i++){
        int v = get<0>(G[u][i]);
        if(!vis[v] && get<1>(G[u][i]) < s) Q.push(v);
      }
    }
    conn_components.push_back(size); 
  }
  int size1 = 0; 
  int size2 = 0; 
  int size3 = 0; 
  int fine = 0; 
  for(int i = 0; i < conn_components.size(); i++){
    if(conn_components[i] == 1) size1++; 
    if(conn_components[i] == 2) size2++; 
    if(conn_components[i] == 3) size3++; 
    if(conn_components[i] >= k) fine++; 
  }
  
  if(k == 1) return fine; 
  else if(k == 2) return fine + size1 / 2; 
  else if(k == 3){
    if(size2 <= size1) return fine + size2 + (size1 - size2) / 3; 
    else return fine + size1 + (size2 - size1) / 2; 
  }
  else{
    int match2 = size2/2; 
    int match31 = min(size1, size3); 
    int rem1 = max(0, size1 - size3); 
    int rem2 = size2%2; 
    int rem3 = max(0, size3-size1); 
    int extra = 0; 
    if(rem1 > 1) extra = (rem1 + rem2 * 2) / 4; 
    else if(rem3) extra += rem2 + (rem3 - rem2) / 2; 
   // else if(rem3 > 0) extra = (3 * rem3 + 2 * rem2) / 4; 
    return extra + match2 + match31 + fine; 
  }
}

void testcase(){
  int n, f;
  long s;
  cin >> n >> k >> f >> s; 
  
  vector<pair<P, int>> tents(n); 
  for(int i = 0; i < n; i++){
    int x, y; 
    cin >> x >> y; 
    tents[i] = {P(x, y), i}; 
  }
  
  Delaunay t;
  t.insert(tents.begin(), tents.end());
  
  vector<vector<pair<int, long>>> G(n);
  vector<long> cand;
  EdgeV edges;
  edges.reserve(3*n); 
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });
  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      uf.link(c1, c2);
      G[c1].push_back({c2, get<2>(*e)});
      G[c2].push_back({c1, get<2>(*e)}); 
      cand.push_back(get<2>(*e));
      if (--n_components == 1) break;
    }
  }
  
  int second = algo(G, s, n); 
  sort(cand.begin(), cand.end());
  int l = 0;
  int r = cand.size() -1 ;
  long res = 0; 
  while(l <= r){
    int m = (l + r) / 2;
    int now = algo(G, cand[m], n);
    if(now >= f && m < cand.size() - 1 && algo(G, cand[m + 1], n) < f){ res = cand[m]; break;}  
    else if(now >= f && m == cand.size() - 1){ res = cand[m]; break;} 
    else if(now >= f) l = m + 1; 
    else if(now < f) r = m - 1;
  }
  cout << res << " " << second << endl; 
  
}

int main(){
  ios_base::sync_with_stdio(false);
  cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0;
}
