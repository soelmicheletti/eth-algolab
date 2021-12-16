#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<string>
#include<limits.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

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
  int count = 0; 
  for (int i = 0; i < n; ++i) {
    // mate_map[i] != NULL_VERTEX: the vertex is matched
    // i < mate_map[i]: visit each edge in the matching only once
    if (mate_map[i] != NULL_VERTEX && i < mate_map[i]) count++;
  }
  return count; 
}


void testcase(){
  int w, h; 
  cin >> w >> h; 
  vector<vector<bool>> B(h, vector<bool>(w, false));
  
  int count = 0; 
  for(int i = 0; i < h; i++){
    string s; cin >> s; 
    for(int j = 0; j < w; j++){
      if(string(1, s[j]) == "."){
        B[i][j] = true; 
        count++;
      }
    }
  }
  
  graph G(h * w);
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      if(B[i][j]){
          if(j != w - 1 && B[i][j + 1]) boost::add_edge(i * w + j, i * w + j + 1, G);
          if(j != 0 && B[i][j - 1]) boost::add_edge(i * w + j, i * w + j - 1, G);
          if(i != h - 1 && B[i+1][j]) boost::add_edge(i * w + j, (i + 1) * w + j, G);
          if(i != 0 && B[i-1][j]) boost::add_edge(i * w + j, (i - 1) * w + j, G);
      }
    }
  }

  int res = maximum_matching(G);
  if(res * 2 == count) cout << "yes" << endl; 
  else cout << "no" << endl; 
}

int main(){
  ios_base::sync_with_stdio(false);
  int n; cin >> n; 
  for(int i = 0; i < n; i++) testcase(); 
  return 0; 
}
