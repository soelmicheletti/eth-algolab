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

std::ostream& operator<<(std::ostream& o, const Edge& e) {
  return o << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e);
}

int algo(Delaunay &t, vector<vector<long>> &bones, long s, int n, EdgeV &edges){
  vector<int> closest(n, 0); 
  for(int i = 0; i < n; i++){
    auto pointer = upper_bound(bones[i].begin(), bones[i].end(), s/4);
    int new_bones = (pointer==bones[i].end()) ? bones[i].size() : pointer-bones[i].begin();
    closest[i] = new_bones; 
  }
  
  vector<int> res(n);
  for(int i = 0; i < n; i++) res[i] = closest[i];
  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2 && get<2>(*e) <= s) {
      uf.link(c1, c2);
      int tmp = res[c1];
      res[c1] += res[c2];
      res[c2] += tmp;
      if (--n_components == 1) break;
    }
  }
  
  int max = 0; 
  for(int i = 0; i < n; i++){
    if(res[i] > max) max = res[i]; 
  }
  return max; 
}


void testcase(){
  int n, m, k;
  long s; 
  cin >> n >> m >> s >> k; 
  typedef std::pair<K::Point_2,int> IPoint;
  std::vector<IPoint> oaks;
  oaks.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    K::Point_2 P(x,y); 
    oaks.emplace_back(P, i);
  }
  Delaunay t;
  t.insert(oaks.begin(), oaks.end());
  
  vector<vector<long>> bones(n); 
  vector<long> tries; 
  for(int i = 0; i < m; i++){
    int x, y; 
    cin >> x >> y; 
    K::Point_2 P(x, y); 
    long d = CGAL::squared_distance(P,t.nearest_vertex(P)->point()); 
    bones[t.nearest_vertex(P) -> info()].push_back(d); 
    tries.push_back(d * 4); 
  }
  
  for(int i = 0; i < n; i++) sort(bones[i].begin(), bones[i].end());
  

  EdgeV edges;
  edges.reserve(3*n); 
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
    tries.push_back(t.segment(e).squared_length());
  }
  sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });

  
  cout << algo(t, bones, s, n, edges) << " ";
  
  sort(tries.begin(), tries.end()); 

  int left = 0; 
  int right = tries.size() - 1; 
  while(left <= right){
    int mid = (left + right) / 2; 
    int part = algo(t, bones, tries[mid], n, edges);
    if(part >= k && mid >= 1 && algo(t, bones, tries[mid - 1], n, edges) < k){ cout << tries[mid] << endl; left = right + 1; break; }
    if(part < k) left = mid + 1; 
    if(part >= k && mid == 0){cout << tries[0] << endl; left = right + 1; break;}
    if(part >= k) right = mid - 1; 
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  int t; 
  cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0;
}
