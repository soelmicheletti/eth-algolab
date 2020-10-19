#include<iostream>
#include<vector>
#include<tuple>
#include<limits.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std; 

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

int dijkstra_path(const weighted_graph &G, int s, int t, std::vector<vertex_desc> &path) {
  int n = boost::num_vertices(G);
  std::vector<int>         dist_map(n);
  std::vector<vertex_desc> pred_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G)))
    .predecessor_map(boost::make_iterator_property_map(
      pred_map.begin(), boost::get(boost::vertex_index, G))));

  int cur = t;
  path.clear(); path.push_back(cur);
  while (s != cur) {
    cur = pred_map[cur];
    path.push_back(cur);
  }
  std::reverse(path.begin(), path.end());
  return dist_map[t];
}




void testcase(){
  int n, m, k, x, y; 
  cin >> n >> m >> k >> x >> y; 
  vector<vector<tuple<int, int>>> G(n * (k + 1)); 
  for(int i = 0; i < m; i++){
    int a, b, c, d; 
    cin >> a >> b >> c >> d; 
    if(d == 0){
      for(int j = 0; j < k + 1; j++){
        G[a + n * j].push_back(make_tuple(b + n * j, c)); 
        G[b + n * j].push_back(make_tuple(a + n * j, c));
      }
    }
    else if(d == 1){
      for(int j = 0; j < k; j++){
        G[a + n * j].push_back(make_tuple(b + n * (j + 1), c)); 
        G[b + n * j].push_back(make_tuple(a + n * (j + 1), c));
      }
      G[a + n * k].push_back(make_tuple(b + n * k, c)); 
      G[b + n * k].push_back(make_tuple(a + n * k, c));
    }
  }
  
  /*for(int i = 0; i < G.size(); i++){
    for(int j = 0; j < G[i].size(); j++){
      cout << get<0>(G[i][j]) << " " << get<1>(G[i][j]) << endl; 
    }
    cout << endl; 
  }*/
  
  
  weighted_graph GG(n * (k + 1));
  weight_map weights = boost::get(boost::edge_weight, GG);

  edge_desc e;
  for(int i = 0; i < G.size(); i++){
    for(int j = 0; j < G[i].size(); j++){
      e = boost::add_edge(i, get<0>(G[i][j]), GG).first; weights[e] = get<1>(G[i][j]);
    }
  }
  cout << dijkstra_dist(GG, x, y + k * n) << "\n";
  
}

int main(){
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
