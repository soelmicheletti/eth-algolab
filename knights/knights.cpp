#include<iostream>
#include<vector>
#include<tuple>
#include<limits.h> 
#include<algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std; 

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

int m, n; 

int out(int row, int col){
  return 2 * (row * m + col); 
}

int in(int row, int col){
  return 2 * (row * m + col) + 1; 
}

void testcase(){
  int k, C; 
  cin >> m >> n >> k >> C; 
  if(n == 0 || m == 0 || k == 0) cout << 0 << endl;
  else{
  graph G(n * m * 2);
  edge_adder adder(G);
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if(j != 0){
        adder.add_edge(out(i, j), in(i, j - 1), 1);
      }
      if(j != m - 1){
        adder.add_edge(out(i, j), in(i, j + 1), 1);
      }
      if(i != 0){
        adder.add_edge(out(i, j), in(i - 1, j), 1);
      }
      if(i != n - 1){
        adder.add_edge(out(i, j), in(i + 1, j), 1);
      }
      adder.add_edge(in(i, j), out(i, j), C);
    }
  }
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  for(int i = 0; i < k; i++){
    int v, u; 
    cin >> v >> u; 
    adder.add_edge(v_source, in(u, v), 1);
  }
  for(int i = 1; i < n - 1; i++){
    adder.add_edge(2 * (i * m), v_sink, 1);
    adder.add_edge(2 * (i * m + m - 1), v_sink, 1);
  }
  
  for(int j = 1; j < m - 1; j++){
    adder.add_edge(2 * j, v_sink, 1);
    adder.add_edge(2 * (m * (n - 1) + j), v_sink, 1);
  }
  
  adder.add_edge(0, v_sink, 2);
  adder.add_edge(2 * (m - 1), v_sink, 2);
  adder.add_edge(2 * (n - 1) * m, v_sink, 2);
  adder.add_edge(2 * ((n - 1) * m + m - 1), v_sink, 2);
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  cout << flow << "\n";  
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0; 
}
