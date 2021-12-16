#include<iostream>
#include<tuple>
#include<vector>
#include<limits.h>
#include <iterator> 
#include <map> 
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include<string>

using namespace std; 

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

int maximum_matching(const graph &G) {
  int n = boost::num_vertices(G);
  std::vector<vertex_desc> mate_map(n);  // exterior property map
  const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();

  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int res = 0; 
  for (int i = 0; i < n; ++i) {
    // mate_map[i] != NULL_VERTEX: the vertex is matched
    // i < mate_map[i]: visit each edge in the matching only once
    if (mate_map[i] != NULL_VERTEX && i < mate_map[i]) res++;
  }
  return res; 
}

void testcase(){
  int n, e, f; 
  cin >> n >> e >> f; 
  vector<int> tags; 
  map<string, vector<int>> S; 

  for(int i = 0; i < n; i++){
    for(int j = 0; j < e; j++){
      string g; cin >> g; 
      if(S.find(g) != S.end()){
        (S.find(g) -> second).push_back(i); 
      }
      else{
        vector<int> k; 
        k.push_back(i); 
        S.insert(pair<string, vector<int>>(g, k));
      }
    }
  }
  
  vector<vector<int>> R(n, vector<int>(n, 0));
  for (auto itr = S.begin(); itr != S.end(); itr++){
    vector<int> k = itr -> second;
    for(int i = 0; i < k.size(); i++){
      for(int j = i + 1; j < k.size(); j++){
        R[k[i]][k[j]]++; 
        R[k[j]][k[i]]++; 
      }
    }
  }
  
  graph G(n);
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(R[i][j] > f){
        boost::add_edge(i, j, G);
      }
    }
  }
  
  if(maximum_matching(G)< n / 2){
    cout << "optimal" << "\n";
  }
  else{
    cout << " not optimal" << "\n";
  }
}

int main(){
  int t = 0; cin >> t; 
  for(int i = 0; i < t; i++){
    testcase(); 
  }
  return 0; 
}
