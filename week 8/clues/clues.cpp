#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Triangulation_vertex_base_with_info_2.h>
#include<CGAL/Triangulation_data_structure_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

bool bipartite(Delaunay &T, int n, long r){
  vector<int> color(n, -1); 
  
  for(auto v = T.finite_vertices_begin(); v != T.finite_vertices_end(); v++){
    if(color[v -> info()] != -1) continue;
    
    color[v -> info()] = 0;
    queue<Delaunay::Vertex_handle> Q;
    Q.push(v); 
  
    while(!Q.empty()){
      Delaunay::Vertex_handle u = Q.front(); 
      Q.pop(); 
      Delaunay::Vertex_circulator c = T.incident_vertices(u); 
        do{
          if(!T.is_infinite(c) && CGAL::squared_distance(u -> point(), c -> point()) <= r){
            if(color[c -> info()] == color[u -> info()]) return false;
            else if(color[c -> info()] == -1){
              color[c -> info()] = 1 - color[u -> info()]; 
              Q.push(c); 
            }
          }
          Delaunay::Vertex_circulator c2 = T.incident_vertices(c);
          do {
            if (CGAL::squared_distance(u->point(), c2->point()) <= r && !T.is_infinite(c2)) {
              if (color[c2->info()] == -1) {
                color[c2->info()] = 1 - color[u -> info()];
                Q.push(c2);
              }
              else if (color[c2->info()] == color[u -> info()]) {
                return false; 
              }
            }
          } while (++c2 != T.incident_vertices(c));
        } while(++c != T.incident_vertices(u));
    }
  }
  return true; 
}

void connected_components(Delaunay &T, int n, long r){
  int k = 0; 
  for(auto v = T.finite_vertices_begin(); v != T.finite_vertices_end(); v++){
    if(v -> info() == -1){
      v -> info() = k; 
      stack<Delaunay::Vertex_handle> S;
      S.push(v);
      while(!S.empty()){
        Delaunay::Vertex_handle u = S.top(); 
        S.pop(); 
        Delaunay::Vertex_circulator c = T.incident_vertices(u); 
        do{
          if(!T.is_infinite(c) && c -> info() == -1 && CGAL::squared_distance(u -> point(), c -> point()) <= r){
            c -> info() = k; 
            S.push(c); 
          }
        } while(++c != T.incident_vertices(u));
      }
      k++;
    }
  }
}

void testcase(){
  int n, m;
  long r;
  cin >> n >> m >> r;
  r = r * r; 
  
  vector<P> stations(n);
  for(int i = 0; i < n; i++) cin >> stations[i];
  
  Delaunay T;
  T.insert(stations.begin(), stations.end());
  
  int k = 0;
  for(auto v = T.finite_vertices_begin(); v != T.finite_vertices_end(); v++){
    v -> info() = k++; 
  }
  bool is_bipartite = bipartite(T, n, r);
  
  for(auto v = T.finite_vertices_begin(); v != T.finite_vertices_end(); v++){
    v -> info() = -1; 
  }
  
  connected_components(T, n, r);
  
  for(int i = 0; i < m; i++){
    P holmes; P watson;
    cin >> holmes >> watson;
    if(!is_bipartite) cout << "n";
    else if(CGAL::squared_distance(holmes, watson) <= r) cout << "y";
    else if(CGAL::squared_distance(holmes, T.nearest_vertex(holmes) -> point()) > r) cout << "n";
    else if(CGAL::squared_distance(watson, T.nearest_vertex(watson) -> point()) > r) cout << "n";
    else if(T.nearest_vertex(holmes) -> info() == T.nearest_vertex(watson) -> info()) cout << "y";
    else cout << "n"; 
  }
  cout << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for(int i = 0; i < t; i++) testcase();
  return 0;
}
