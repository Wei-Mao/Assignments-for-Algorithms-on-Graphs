#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/* using std::vector; */
/* using std::pair; */
class Directed_Graph
{
  private:
    vector<vector<int>> adjacency_list; // For each vertex, a list of adjacent vertices
    vector<vector<int>> adjacency_list_reverse;

  public:
    void Data_Read()
    {
      size_t n, m;  // n vertices and m edges
      std::cin >> n >> m;
      adjacency_list.resize(n);
      adjacency_list_reverse.resize(n);
      for (size_t i = 0; i < m; i++) {
	int x, y;
	std::cin >> x >> y;  // 1-based
	adjacency_list[x - 1].push_back(y - 1);  // convert to 0-based index
	adjacency_list_reverse[y - 1].push_back(x - 1);
	// The index of the first dimension of the 2D corresponds to the vertex number.
	// Both for original and reverse Adj. List representation.
      }
    }

    Directed_Graph()
    {}
   
    void explore(int v, vector<vector<int>> &adj_list, vector<string> &vertex_status, bool &is_cycle, stack<int> &stack_order)
    {
      /* Check whether there is a cycle containing vertex v. 
	 Input:
	    v(int): Zero-based index for the given vertex.
	    adj_list(vector<vector<int>>): Adjacency List for Original Graph or the Graph with Graph edge reversed.
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
      for(int i(0); i < adj_list[v].size(); i++)
      {
	int w = adj_list[v][i];
	if(vertex_status[w] == "begin")
	{
	  is_cycle = true;
	}
	if(vertex_status[w] == "unvisited")
	{
	  explore(w, adj_list, vertex_status, is_cycle, stack_order);
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
	  explore(v, adjacency_list, vertex_status, is_cycle, stack_order);
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
	  explore(v, adjacency_list, vertex_status, is_cycle, stack_order);
	}
      }
      return stack_order;
    }    

    stack<int> DFS(vector<vector<int>> adj_list)
    {
      /* Depth First Search on the Original Graph.
	 
	 Input: 
	    adj_list: the Adjacency List of the Original or Reverse Graph.
	 Return the reversed linear order, ignoring the cycle.
      */
      vector<string> vertex_status(adj_list.size(), "unvisited");
      bool is_cycle = false;
      stack<int> stack_order;
      for(int v(0); v < adj_list.size(); v++)
      {
	if(vertex_status[v] == "unvisited")
	{
	  explore(v, adj_list, vertex_status, is_cycle, stack_order);
	}
      }

      return stack_order;   // reverse order. smallest postorder first in but last out.
    }

    int num_sccs()
    {
      /* Compute the number of strongly connected components(SCC) in the graph.
	 Return: The number SCCs
	 Time Complexity:O(|V| + |E|)
	 Space Complexity:O(|V|)
      */
      stack<int> post_order;
      post_order = DFS(adjacency_list_reverse); // Largest postorder last in, will first out.

      vector<string> vertex_status(adjacency_list.size(), "unvisited");
      bool is_cycle = false;
      stack<int> stack_order;
      int number_of_SCCs(0);
      while(!post_order.empty())
      {
	int v = post_order.top(); // Largest post_order comes out first.
	post_order.pop();
	if(vertex_status[v] == "unvisited")
	{
	  explore(v, adjacency_list, vertex_status, is_cycle, stack_order);
	  number_of_SCCs ++;
	}
      }

      return number_of_SCCs; 
    }
};



int main() {
  // https://stackoverflow.com/questions/9490349/instantiate-class-with-or-without-parentheses
  Directed_Graph graph;
  graph.Data_Read();
  cout << graph.num_sccs() << endl;
  /* std::cout << number_of_strongly_connected_components(adj); */
}
