#include <iostream>
#include <vector>
using namespace std;

using std::vector;
using std::pair;


class Undirected_Graph
{
  private:
    vector<vector<int>> adjacency_list;

  public:
    Undirected_Graph(vector<vector<int>> _adjacency_list):
      adjacency_list(_adjacency_list)
    {
    }
    //Since C++11, you can copy arrays directly with std::array:

    void explore(int v, vector<bool> &visited)
    {
      /* Mark all vertices reachable from given vertex with index v
	 Input:
	    v(int): Zero-based index for the given vertex.
	    visited(vector(bool)): Marker of visit for all nodes.
	 Output:
	    Void.
	 Time Complexity: O(# of edges in the connected component of v)
	 Space Complexity: O(|V|*max number of adjacent vertices)
      */
      visited[v] = true;
      for(int i(0); i < adjacency_list[v].size(); i++)
      {
	int w = adjacency_list[v][i];;
	if(!visited[w])
	{
	  explore(w, visited);
	}
      }
    }

    int reach(int x, int y) 
    {
      /* Check the reachability between vertices x and y
	 Input: 
	    x(int): zero-based index of the vertex
	    y(int): zero-based index of another vertex
	 Output:
	    1 if there is a path between x and y, 0 otherwise.
	 Time Complexity: the same as explore.
	 Space Complexity: the same as explore.
      */
      vector<bool>  visited(adjacency_list.size(), false);
      explore(x, visited);
      if(visited[y] == true) 
      {
	return 1;
      }
      else
      {
        return 0;
      }
    }
};


int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());  // dynamic array of an dynamic array.
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  // In the input format, the vertices are numbered from one.
  // In the adjacency list, we simply adopt the indices of the array as the vertex number. 
  // Index starts at zero.
  }

  Undirected_Graph graph(adj);
  int x, y;
  std::cin >> x >> y;
  std::cout << graph.reach(x - 1, y - 1);

  return 0;
}
