#include <iostream>
#include <vector>
#include <limits>
using namespace std;
const int int_max = numeric_limits<int>::max();

using std::vector;
class Directed_Graph
{
  private:
    vector<vector<int>> adj;
    vector<vector<int>> cost;
  
  public:
    void Data_Read()
    {
      int n, m;
      std::cin >> n >> m;
      adj.resize(n);
      cost.resize(n);
      /* vector<vector<int> > adj(n, vector<int>()); */
      /* vector<vector<int> > cost(n, vector<int>()); */
      for (int i = 0; i < m; i++) {
	int x, y, w;
	std::cin >> x >> y >> w;
	adj[x - 1].push_back(y - 1);
	cost[x - 1].push_back(w);
      }

    }
    void ensure_connected(vector<vector<int>> &adj_augmented, vector<vector<int>>  &cost_augmented)
    {
      /*
	 What if the negative cycle is unreachable from the source vertex?
	 The simplest approach is to add an extra vertex and add an edge of length 1 from this vertex to each vertex of the initial graph.
	 you have to set the source to be the added vertex.
      */
      adj_augmented.resize(adj.size() + 1);
      cost_augmented.resize(adj.size() + 1);
      int n = adj.size();
      for(int i(0); i < adj.size(); i++)
	for(int j(0); j < adj[i].size(); j++)
	{
	  adj_augmented[i].push_back(adj[i][j]);
	  cost_augmented[i].push_back(cost[i][j]);
	}

      for (int i = 0; i < n; i++)
      {
	adj_augmented[n].push_back(i);
	cost_augmented[n].push_back(1);
      }
    }

    int is_negative_cycle()
    {
      /*
	 Only holds for connected graph.
      */
      vector<vector<int>> adj_augmented;
      vector<vector<int>> cost_augmented;
      ensure_connected(adj_augmented, cost_augmented);
      vector<int> dist(adj_augmented.size(), int_max);
      int source = adj_augmented.size() - 1; // Starting from the added vertex, you can reach the originally unreachable negative cycle.
      dist[source] = 0;
      for(int k(1); k <= adj_augmented.size(); k++)
      {
	for(int i(0); i < adj_augmented.size(); i++)
	  for(int j(0); j < adj_augmented[i].size(); j++)
	  {
	    int u = i;
	    int v = adj_augmented[i][j];
	    int w = cost_augmented[i][j]; //  from u to v

	    // relax
	    if(dist[v] > dist[u] + w && (dist[u] != int_max))
	    {
	      if(k == adj_augmented.size())
	      {
		return 1;
	      }
	      dist[v] = dist[u] + w;
	    }

	  }
      }
      return 0;
    }

};

int main() {
  Directed_Graph graph;
  graph.Data_Read();
  cout << graph.is_negative_cycle() << endl;
  /* int n, m; */
  /* std::cin >> n >> m; */
  /* vector<vector<int> > adj(n, vector<int>()); */
  /* vector<vector<int> > cost(n, vector<int>()); */
  /* for (int i = 0; i < m; i++) { */
  /*   int x, y, w; */
  /*   std::cin >> x >> y >> w; */
  /*   adj[x - 1].push_back(y - 1); */
  /*   cost[x - 1].push_back(w); */
  /* } */
  /* std::cout << negative_cycle(adj, cost); */
}
