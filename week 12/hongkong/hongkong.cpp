#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Gmpq.h>
#include <vector>
#include <queue>
#include <algorithm>
#include<limits.h>

using namespace std; 

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;
typedef Triangulation::Face_handle Face_handle;;
typedef K::Point_2 P;


void testcase(){
  int n,m;
  K::FT r;
  cin >> n >> m >> r;

  vector<P> trees(n);
  for(int i = 0; i < n; i++){
    long x,y;
    cin >> x >> y;
    trees[i] = P(x,y);
  }

  Triangulation t;
  t.insert(trees.begin(),trees.end());

  priority_queue<pair<K::FT,Face_handle>> Q;
  for(auto it = t.all_faces_begin(); it != t.all_faces_end(); ++it){
    if(t.is_infinite(it)){
      it->info() = LONG_MAX;
    } else {
      it->info() = CGAL::squared_radius(it->vertex(0)->point(),
                                        it->vertex(1)->point(),
                                        it->vertex(2)->point());
    }
    Q.push({it->info(),it});
  }

  while(!Q.empty()){
    auto elem = Q.top(); Q.pop();
    K::FT old_max_out = elem.first;
    Face_handle face = elem.second;
  
    for(int i=0;i<3;++i){
      Face_handle fh = face->neighbor(i);
      K::FT l = CGAL::squared_distance(face->vertex((i+1)%3)->point(),
                                       face->vertex((i+2)%3)->point());
      K::FT from_current = std::min(l,face->info());
      if(from_current > fh->info()){
        fh->info()= from_current;
        Q.push({from_current,fh});
      }
    }
  }

  for(int i=0;i<m;++i){
    long x,y;
    P p;
    K::FT s;
    std::cin >> x >> y >> s;
    p = P(x,y);

    Face_handle face = t.locate(p);
    P nearest = t.nearest_vertex(p,face)->point();
    if(CGAL::square((r+s)) > CGAL::squared_distance(p,nearest)){
      cout << 'n';
    } else {
      if(CGAL::square(2*(r+s)) <= face->info()){
        cout << 'y';  
      } else {
        cout << 'n';  
      }
    }
  }
  cout << endl;

}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
