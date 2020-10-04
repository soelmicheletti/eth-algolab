#include<iostream>
#include<vector>
#include<limits.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/squared_distance_2.h>


using namespace std; 

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K:: Ray_2 R; 

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase(int n){
  long x, y, a, b;
  cin >> x >> y >> a >> b;
  R ray(P(x,y), P(a,b));
  vector<S> segm(n); 
  for(int i = 0; i < n; i++){
    long r, s, t, u;
    cin >> r >> s >> t >> u;
    segm[i] = S(P(r, s), P(t, u));
  }
  random_shuffle(segm.begin(),segm.end());
  P res;  
  bool flag = false; 
  K::FT min(numeric_limits<double>::max());
  
  for(int i = 0; i < n; i++){
    if(min< CGAL::squared_distance(P(x,y),segm[i])) continue;
    if(CGAL::do_intersect(segm[i], ray)){
      flag = true; 
      auto o = CGAL::intersection(ray,segm[i]);
      if(const P* op = boost::get<P>(&*o)){
          K::FT d(CGAL::squared_distance(P(x,y),*op));
          if(d < min){
            res = *op;
            min = d;
          }
      }else if( const S* os = boost::get<S>(&*o)){
          P source = os->source();
          P target = os->target();
          K::FT ds(CGAL::squared_distance(P(x,y),source));
          if(ds < min){
            res = source;
            min = ds;
          }
          K::FT dt(CGAL::squared_distance(P(x,y),target));
          if(dt < min){
            res = target;
            min = dt;
          }
      } 
    }
  }
  
  if(flag){
    cout << long(floor_to_double(res.x())) << " " << long(floor_to_double(res.y())) <<  "\n"; 
  } else{ cout << "no" << "\n";}
  
}


int main(){
  ios_base::sync_with_stdio(false);
 bool flag = true; 
  while(flag){
    int n; cin >> n; 
    if(n == 0){
      flag = false; 
      break; 
    }
    else{
      testcase(n);
    }
  }
  return 0; 
}
