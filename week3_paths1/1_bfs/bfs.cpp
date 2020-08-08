#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

/* using std::vector; */
/* using std::queue; */
class Undirected_Graph
{
  private:
    vector<vector<int>> adjacency_list; // For each vertex, a list of adjacent vertices.
    int v1, v2;

  public:
    void Data_Read()
    {
      size_t n, m;  // n vertices and m edges
      std::cin >> n >> m;
      adjacency_list.resize(n);
      for (size_t i = 0; i < m; i++)
      {
	int x, y;
	std::cin >> x >> y;  // 1-based
	adjacency_list[x - 1].push_back(y - 1);  // convert to 0-based index
	adjacency_list[y - 1].push_back(x - 1);  // Note that here is the Undirected_Graph !!!!
	// The index of the first dimension of the 2D corresponds to the vertex number.
      }
      // convert to zero-based;
      cin >> v1 >> v2;
      v1--;
      v2--;
    }

    Undirected_Graph() {}

    vector<int> BFS(int S)
    {
      /* Breadth-First Search on the Directed_Graph
	 Input:
	    S(int): Index of the specified origin (zero-based).
	 Return:
	    vector<int>. The vector of distances from all vertices to the origin S.
	 Time Complexity: O(|V| + |E|)
	 Space Complexity: O(|V|)
      */
      int num_of_vertices = adjacency_list.size();
      vector<int> dist(num_of_vertices, num_of_vertices);  // num_of_vertices indicates unreachable vertex.
      vector<int> prev(num_of_vertices, -1);  // parent of vertex in the shortest path tree.
      dist[S] = 0;
      queue<int> queue_vertex;
      queue_vertex.push(S);

      while(!queue_vertex.empty())
      {
	int u = queue_vertex.front();
	queue_vertex.pop();
	for(int i(0); i < adjacency_list[u].size(); i++)
	{
	  int v = adjacency_list[u][i];
	  if(dist[v] == num_of_vertices)  
	  {
	    // v has not been  discoveried
	    // enqueue v
	    queue_vertex.push(v);
	    dist[v] = dist[u] + 1;
	    prev[v] = u;
	  }
	}
      }
      return dist;
    }

    int compute_distance(int u, int v)
    {
      /* Compute the distance from u to v.
	 Input: 
	    u and v are the index of the two vertices. (zero-based)
	 Return:
	    The distance between them if there is a path between them. Otherwise, -1.
      */

      vector<int> dist = BFS(u);
      return dist[v] != adjacency_list.size() ? dist[v] : -1;
    }

    int process()
    {
      return compute_distance(v1, v2);
    }


};

int main() {
  Undirected_Graph graph;
  graph.Data_Read();
  cout << graph.process() << endl;

  /* int n, m; */
  /* std::cin >> n >> m; */
  /* vector<vector<int> > adj(n, vector<int>()); */
  /* for (int i = 0; i < m; i++) { */
  /*   int x, y; */
  /*   std::cin >> x >> y; */
  /*   adj[x - 1].push_back(y - 1); */
  /*   adj[y - 1].push_back(x - 1); */
  /* } */
  /* int s, t; */
  /* std::cin >> s >> t; */
  /* s--, t--; */
  /* std::cout << distance(adj, s, t); */
}
