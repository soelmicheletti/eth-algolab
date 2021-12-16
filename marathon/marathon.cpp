#include <iostream>
#include <vector>
#include<limits.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std; 

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;




int n; 
int m; 
int s; 
int f; 
vector<vector<int>> cap; 

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

vector<int> dijkstra_path(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int>         dist_map(n);
  std::vector<vertex_desc> pred_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G)))
    .predecessor_map(boost::make_iterator_property_map(
      pred_map.begin(), boost::get(boost::vertex_index, G))));
  return dist_map;
}

void testcase(){
  cin >> n >> m >> s >> f; 
  cap.clear(); 
  cap.resize(n, vector<int>(n, INT_MAX)); 
  vector<vector<int>> B(n, vector<int>(n, INT_MAX));
  for(int i = 0; i < m; i++){
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    if(d < B[a][b]){
      B[a][b] = d;
      B[b][a] = d;
      cap[a][b] = c;
      cap[b][a] = c;
    }
    else if(d == B[a][b]){
      cap[a][b] += c;
      cap[b][a] += c;
    }
  }
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  edge_desc e;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(B[i][j] != INT_MAX){
        e = boost::add_edge(i, j, G).first; weights[e] = B[i][j]; 
        //e = boost::add_edge(j, i, G).first; weights[e] = B[i][j]; 
      }
    }
  }

  vector<int> dist = dijkstra_path(G, s, f);
  vector<int> ret = dijkstra_path(G, f, s); 
  graph M(n + 2);
  edge_adder adder(M);
    
  adder.add_edge(n, s, INT_MAX); // from, to, capacity
  adder.add_edge(f, n + 1, INT_MAX); 
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(B[i][j] != INT_MAX && dist[i] + B[i][j] + ret[j] == dist[f]){
        adder.add_edge(i, j, cap[i][j]); 
      }
    }
  }
  long flow = boost::push_relabel_max_flow(M, n, n + 1);
  cout << flow << endl;
  
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0;
}
