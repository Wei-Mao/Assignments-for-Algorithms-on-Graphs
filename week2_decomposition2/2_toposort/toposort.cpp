#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

/* using std::vector; */
/* using std::pair; */

class Directed_Graph
{
  private:
    vector<vector<int>> adjacency_list; // For each vertex, a list of adjacent vertices

  public:
    Directed_Graph(vector<vector<int>> adjacency_list_):
      adjacency_list(adjacency_list_)
    {}
   
    void explore(int v, vector<string> &vertex_status, bool &is_cycle, stack<int> &stack_order)
    {
      /* Check whether there is a cycle containing vertex v. 
	 Input:
	    v(int): Zero-based index for the given vertex.
	    vertex_status(vector<string>): "unvisited" if vertex has not been visited yet;
					    "begin" if explore(v) has started;
					    "end" if explore(v) has terminated.
	    is_cycle(bool): true if detecting a cycle.
	    stack_order(stack<int>): store the linear order.
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
	  explore(w, vertex_status, is_cycle, stack_order);
	}
      }
      vertex_status[v] = "end";
      stack_order.push(v);  // O(1)
    }

    int is_cycle_DFS()
    {
      /* Check whether the graph contains a graph by detecting the back edge.
	 Time Complexity: O(|V| + |E|)
	 Space Complexity: O(|V|)
      */
      vector<string> vertex_status(adjacency_list.size(), "unvisited");
      bool is_cycle = false;
      stack<int> stack_order;
      for(int v(0); v < adjacency_list.size(); v++)
      {
	if(vertex_status[v] == "unvisited")
	{
	  explore(v, vertex_status, is_cycle, stack_order);
	}
      }

      int res = is_cycle ? 1 : 0;
      return res;
    }

    stack<int> topogical_sort()
    {
      /* Linearly order the directed graph.
	 A topological sort of a DAG G=(V, E) is a linear ordering of all 
	 its vertices such that if G contains an edge (u,v), then u appers before v in the ordering.
	 Algorithm: Call DFS(G) to compute postorder number. 
	 As each vertex is finished, insert it to the stack(Last In First Out).
	 Time Complexity: O(|V| + |E|)
	 Space Complexity:O(|v|)
      */
      vector<string> vertex_status(adjacency_list.size(), "unvisited");
      bool is_cycle = false;
      stack<int> stack_order;
      for(int v(0); v < adjacency_list.size(); v++)
      {
	if(vertex_status[v] == "unvisited")
	{
	  explore(v, vertex_status, is_cycle, stack_order);
	}
      }

      return stack_order;  
      // Reverse linear order of graph.
      // stack_order.top()
      // stack_order.pop()
      // repeat the above 2 commands to output the correct linear order.
    }
};


vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  //write your code here
  return order;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  Directed_Graph graph(adj);
  stack<int> order = graph.topogical_sort();
 while(!order.empty())
 {
    int top = order.top();  // O(1)
    order.pop(); // O(1)
    std::cout << top + 1 << " ";
  }
}
