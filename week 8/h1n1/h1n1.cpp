#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<limits.h>
#include<tuple>
#include<queue>

using namespace std; 

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::All_faces_iterator Face_iterator;
typedef K::Point_2 P;



struct pair_sorter {
    bool operator() (const pair<Triangulation::Face_handle, K::FT> &i, const pair<Triangulation::Face_handle, K::FT> &j) const {
        return i.second > j.second;
    }
};

void testcase(Index n){
  vector<P> infected(n); 
  for(int i = 0; i < n; i++){
    P p; 
    cin >> p; 
    infected[i] = p; 
  }
  
  Triangulation t; 
  t.insert(infected.begin(), infected.end());
  
  multiset<pair<Triangulation::Face_handle, K::FT>, pair_sorter> Q; 
  for(Triangulation::Face_handle f = t.all_faces_begin(); f != t.all_faces_end(); f++){
    if(!t.is_infinite(f)) f -> info() = 0; 
    else{
      f -> info() = INT_MAX; 
      for(int i = 0; i < 3; i++){
        if(!t.is_infinite(f -> neighbor(i))) Q.insert({f -> neighbor(i), t.segment(f, i).squared_length()});
      }
    }
  }
  
  while(Q.size() > 0){
    Triangulation::Face_handle f = (*(Q.begin())).first; 
    K::FT d = (*(Q.begin())).second;
    Q.erase(Q.begin());
    if(f -> info() == 0){
      f -> info() = d; 
      for(int i = 0; i < 3; i++){
        if(!t.is_infinite(f -> neighbor(i)) && f -> neighbor(i) -> info() == 0){
          Q.insert({f -> neighbor(i), min(d, t.segment(f, i).squared_length())});
        }
      }
    }
  }
  
  int m; 
  cin >> m; 
  for(int i = 0; i < m; i++){
    P q; cin >> q; 
    long long d; cin >> d; 
    auto nearest = t.nearest_vertex(q); 
    if(CGAL::squared_distance(q, nearest -> point()) < d){
      cout << "n";
    }
    else{
      Triangulation::Face_handle f = t.locate(q); 
      if(t.is_infinite(f) || f -> info() >= 4 * d) cout << "y";
      else cout << "n";
    }
  }
  cout << endl; 
}

int main(){
  ios_base::sync_with_stdio(false); 
  while(true){
    Index n; cin >> n; 
    if(n == 0) break; 
    testcase(n); 
  }
  return 0; 
}
