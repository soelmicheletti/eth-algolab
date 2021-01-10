#include <iostream>
#include<algorithm>
#include<utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include<string>

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
  int letters = 'Z' - 'A' + 1; 
  int h, w; cin >> h >> w; 
  string word; cin >> word; 
  vector<string> front; 
  vector<vector<int>> P(letters, vector<int>(letters, 0)); 
  for(int i = 0; i < h; i++){
    string k; cin >> k;
    front.push_back(k); 
  }
  vector<string> back; 
  for(int i = 0; i < h; i++){
    string k; cin >> k; 
    back.push_back(k); 
    for(int j = 0; j < w; j++){
      char a = front[i][j]; 
      char b = k[w - j - 1]; 
      P[max(a - 'A', b - 'A')][min(a - 'A', b - 'A')]++; 
    }
  }
  
  
  
  graph G(letters + letters * letters + 2);
  edge_adder adder(G);
  int source = letters + letters * letters;
  int sink = letters + letters * letters + 1; 
  for(int i = 0; i < word.size(); i++){
    adder.add_edge(source, word[i] - 'A', 1); 
  }
  
  for(int i = 0; i < letters; i++){
    for(int j = 0; j < letters; j++){
      if(P[i][j] != 0){
        adder.add_edge(i, letters + letters * i + j, P[i][j]); 
        adder.add_edge(j, letters + letters * i + j, P[i][j]); 
        adder.add_edge(letters + letters * i + j, sink, P[i][j]); 
      }
    }
  }
  

  long flow = boost::push_relabel_max_flow(G, source, sink);
  if(flow == word.size()) cout << "Yes" << endl; 
  else cout << "No" << endl; 
}

int main() {
  ios_base::sync_with_stdio(false); 
  int t; cin >> t; 
  for(int i = 0; i < t; i++) testcase(); 
  return 0;
}
