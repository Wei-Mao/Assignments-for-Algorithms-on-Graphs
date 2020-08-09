#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

/* using std::vector; */
/* using std::queue; */
/* using std::pair; */
/* using std::priority_queue; */
class Vertex
{
  public:
    int ID; //  zero-based index
    int dist; // distance estimate

    Vertex(int _ID, int _dist)
      :ID(_ID), dist(_dist)
    {
    }
};

class Compare_Dist
{
  public:
    bool operator () (Vertex & v1, Vertex & v2)
    {
      return v1.dist > v2.dist;  // Vertex of  smaller distance  has precedence.
    }
};

class Directed_Graph 
{
  private:
    vector<vector<int>> adj_list;
    vector<vector<int>> cost;
    int s, t;
    int int_max = numeric_limits<int>::max();
  
  public:
    Directed_Graph() {}
    void Data_Read()
    {
      int n, m;
      std::cin >> n >> m;
      adj_list.resize(n);
      cost.resize(n);

      for (int i = 0; i < m; i++) {
	int x, y, w;
	std::cin >> x >> y >> w;
	adj_list[x - 1].push_back(y - 1);   
	cost[x - 1].push_back(w);
	// convert to zero-based
	// such that index of array element corresponds to the vertex index.
      }
      std::cin >> s >> t;
      s--, t--;  // convert to zero-based index.
    }

    vector<int> Dijkstra(int source)
    {
      /* Dijkstra Algorithm to find the shortest path length with regard to minimum total weights.
	 Input:
	    source(int): The zero-based index of the source vertex.
	 Return:
	    Vector of distance from source vertex to all other vertices.
	 Remarks: Priority Queue based version.
	 Time Complexity: O((|V| + |E|) log|V|)
	 Space Complexity: O(|V|)
      */
      int num_of_vertices = adj_list.size();
      vector<int> dist(num_of_vertices, int_max);
      dist[source] = 0;
      priority_queue<Vertex , vector<Vertex>, Compare_Dist> H;
      H.push(Vertex(source, dist[source]));

      while(!H.empty())
      /* for(int i(0); i < num_of_vertices; i++) */
      {
	int u = H.top().ID; // return vertex with minimum dist.
	H.pop();
	for(int j(0); j < adj_list[u].size(); j ++)
	{
	  int v = adj_list[u][j];
	  int w = cost[u][j];
	  
	  // check for relaxation
	  if(dist[v] > (dist[u] + w))
	  {
	    dist[v] = dist[u] +w;
	    H.push(Vertex(v, dist[v]));
	  }
	}
      }

      return dist;
    }

    int process()
    {
      vector<int> dist = Dijkstra(s);
      return dist[t] != int_max ? dist[t] : -1;
    }
};


int main() {
  Directed_Graph graph;
  graph.Data_Read();
  cout << graph.process();

  /* int n, m; */
  /* std::cin >> n >> m; */
  /* vector<vector<int> > adj(n, vector<int>()); */
  /* vector<vector<int> > cost(n, vector<int>()); */
  /* for (int i = 0; i < m; i++) { */
  /*   int x, y, w; */
  /*   std::cin >> x >> y >> w; */
  /*   adj[x - 1].push_back(y - 1); */   
  /*   cost[x - 1].push_back(w); */
  /*   // convert to zero-based */
  /*   // such that index of array element corresponds to the vertex index. */
  /* } */
  /* int s, t; */
  /* std::cin >> s >> t; */
  /* s--, t--; */
  /* std::cout << distance(adj, cost, s, t); */
}
