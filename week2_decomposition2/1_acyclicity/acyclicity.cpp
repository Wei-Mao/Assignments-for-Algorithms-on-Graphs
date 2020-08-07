#include <iostream>
#include <vector>
#include <string>
using namespace std;

using std::vector;
using std::pair;

class Directed_Graph
{
  private:
    vector<vector<int>> adjacency_list; // For each vertex, a list of adjacent vertices

  public:
    Directed_Graph(vector<vector<int>> adjacency_list_):
      adjacency_list(adjacency_list_)
    {}
   
    void explore(int v, vector<string> &vertex_status, bool &is_cycle)
    {
      /* Check whether there is a cycle containing vertex v. 
	 Input:
	    v(int): Zero-based index for the given vertex.
	    vertex_status(vector<string>): "unvisited" if vertex has not been visited yet;
					    "begin" if explore(v) has started;
					    "end" if explore(v) has terminated.
	    is_cycle(bool): true if detecting a cycle.
	 Output:Void.
	 Time Complexity: O(# of edges in in the  visited subgraph)
	 Space Complexity: O(1). We takes the reference to vector as input.
	 Remark: Reference at https://stackoverflow.com/questions/261573/best-algorithm-for-detecting-cycles-in-a-directed-graph
      */
      vertex_status[v] = "begin";
      for(int i(0); i < adjacency_list[v].size(); i++)
      {
	int w = adjacency_list[v][i];;
	if(vertex_status[w] == "begin")
	{
	  is_cycle = true;
	}
	if(vertex_status[w] == "unvisited")
	{
	  explore(w, vertex_status, is_cycle);
	}
      }
      vertex_status[v] = "end";
    }

    int is_cycle_DFS()
    {
      /* Check whether the graph contains a graph by detecting the back edge.
	 Time Complexity: O(|V| + |E|)
	 Space Complexity: O(|V|)
      */
      vector<string> vertex_status(adjacency_list.size(), "unvisited");
      bool is_cycle = false;
      for(int v(0); v < adjacency_list.size(); v++)
      {
	if(vertex_status[v] == "unvisited")
	{
	  explore(v, vertex_status, is_cycle);
	}
      }

      int res = is_cycle ? 1 : 0;
      return res;
    }

};


int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  Directed_Graph  graph(adj);
  cout << graph.is_cycle_DFS() << endl;
}
