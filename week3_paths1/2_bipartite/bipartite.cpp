#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/* using std::vector; */
/* using std::queue; */

class Undirected_Graph 
{
  private:
    vector<vector<int>> adjacency_list;
    vector<vector<int>> edge_list;

  public:
    void Data_Read()
    {
      int n, m;
      std::cin >> n >> m;
      adjacency_list.resize(n);
      edge_list.resize(m, vector<int>(2));
      for (int i = 0; i < m; i++) {
	int x, y;
	std::cin >> x >> y;
	edge_list[i][0] = x - 1;
	edge_list[i][1] = y - 1;
	adjacency_list[x - 1].push_back(y - 1);
	adjacency_list[y - 1].push_back(x - 1);  // undirected graph.
      }
    }

    int is_bipartite()
    {
      /* Assign Color to all vertices, either white or black.
	 Return Color Assignments for all vertices.
	 Remarks: The breadth-first search in the problem 1 is not a complete version, which only starts from one origin. If you one graph have more than 1 connected component. It will
	 not reach the other connected component. BFS(S) is analogous to the explore(S) in the depth-first search. Hence. BFS(S) also finds the connected component of S.
	 In other words, the breadth-first search in the video lecture indeed is the one for one connected component. We simply add one external loop to it to consider all connected components. By using markers of visit, we obtain:
	 Time Complexity: O(|V| + |E|)
	 Of course, you can adapt the depth-first search to check for bipartite.
      */
      int num_of_vertices = adjacency_list.size();
      vector<int> color(num_of_vertices, -1);  // -1 means not being assigned.
      queue<int> queue_vertex;
      for(int s(0); s < num_of_vertices; s++)
      {
	if (color[s] == -1)
	{
	  // not visited.
	  queue_vertex.push(s);
	  color[s] = 0;
	  while(!queue_vertex.empty())
	  {
	    int u = queue_vertex.front();
	    queue_vertex.pop();
	    for(int i(0); i < adjacency_list[u].size(); i++)
	    {
	      int v = adjacency_list[u][i];

	      if(color[v] == -1)
	      {
		// v has not been colored.
		// enqueue v
		queue_vertex.push(v);
		/* dist[v] = dist[u] + 1; */
		color[v] = 1 - color[u];
	      }
	      else if (color[u] == color[v])
	      {
		// already colored. Each edge in undirected graph is checked twice.
		return 0; 
	      }
	    }
	  }

	} 
      }

      return 1;
    }

};


int main() {
  Undirected_Graph graph;
  graph.Data_Read();
  cout << graph.is_bipartite();
}
