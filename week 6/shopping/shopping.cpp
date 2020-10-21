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
  int n, m , s; 
  cin >> n >> m >> s; 
  vector<int> S(n, 0); 
  for(int i = 0; i < s; i++){
    int k; cin >> k; 
    S[k] += 1; 
  }

  graph G(n + 1);
  edge_adder adder(G);

  adder.add_edge(0, 1, s);

  for(int i = 0; i < S.size(); i++){
    if(S[i] > 0){
      adder.add_edge(i + 1, n + 1, S[i]);
    }
  }
  
  for(int i = 0; i < m; i++){
    int u, v; 
    cin >> u >> v; 
    adder.add_edge(u + 1, v + 1, 1); 
    adder.add_edge(v + 1, u + 1, 1);
  }
  long flow = boost::push_relabel_max_flow(G, 0, n + 1);
  if(flow >= s){
    cout << "yes" << endl; 
  }
  else{
    cout << "no" << endl; 
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
