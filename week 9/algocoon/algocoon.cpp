#include <iostream>
#include<vector>
#include<limits.h>
#include<algorithm>
#include<utility>
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

void testcase(){
  int n, m; 
  cin >> n >> m; 
  graph G(n);
  edge_adder adder(G);
  for(int i = 0; i < m; i++){
    int u, v, w; 
    cin >> u >> v >> w; 
    adder.add_edge(u, v, w);
  }
  
  int best = INT_MAX; 
  for(int i = 1; i < n; i++){
    int flow = boost::push_relabel_max_flow(G, 0, i);
    if(flow < best) best = flow;
  }
  for(int i = 1; i < n; i++){
    int flow = boost::push_relabel_max_flow(G, i, 0); 
    if(flow < best) best = flow; 
  }
  cout << best << endl; 
}

int main() {
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0;
}
