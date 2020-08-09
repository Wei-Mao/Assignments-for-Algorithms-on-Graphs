#include <iostream>
#include <limits>
#include <vector>
#include <queue>
using namespace std;
const long long int_max = std::numeric_limits<long long>::max();

/* using std::vector; */
/* using std::queue; */
/* using std::pair; */
/* using std::priority_queue; */

class Directed_Graph
{
  private:
    vector<vector<int>> adj;
    vector<vector<int>> cost;
    int s;
  public:
    void Data_Read()
    {
      int n, m;
      std::cin >> n >> m;
      adj.resize(n);
      cost.resize(n);
      for (int i = 0; i < m; i++) {
	int x, y, w;
	std::cin >> x >> y >> w;
	adj[x - 1].push_back(y - 1);
	cost[x - 1].push_back(w);
      }
      std::cin >> s;
      s--; // convert to zero-based index
    }

    void shortest_paths(vector<long long> & dist, vector<int> & reachable, vector<int> &shortest)
    {

      dist.resize(adj.size(), int_max);
      reachable.resize(adj.size(), 1);
      shortest.resize(adj.size(), 1);
      queue<int> q_neg;


      dist[s] = 0;
      for(int k(1); k <= adj.size(); k++)  // |V| iterations
      {
	for(int i(0); i < adj.size(); i++)
	  for(int j(0); j < adj[i].size(); j++)
	  {
	    int u = i;
	    int v = adj[i][j];
	    int w = cost[i][j]; //  from u to v

	    // relax
	    if(dist[v] > dist[u] + w && (dist[u] != int_max))
	    {
	      if(k >= adj.size())
	      {
		/* shortest[v] = 0;  // no shortest path from s to v */
		q_neg.push(v);
	      }
	      dist[v] = dist[u] + w;
	    }

	  }
      }

      for(int i(0); i < adj.size(); i++)
      { 
	if (dist[i] ==  int_max)
	{
	  reachable[i] = 0; // i is unreachable from s 
	}
      }

      // Breadth First Search
      // Process(Dequeue Parent) -> Discover(Enqueue Child) until empty
      while(!q_neg.empty())
      {
	int u = q_neg.front();
	q_neg.pop();
	shortest[u] = 0;
	// visit children
	for(int i(0); i < adj[u].size(); i++)
	{
	  int v = adj[u][i];
	  if(shortest[v])
	  {
	    q_neg.push(v);
	  }
	}
      }
    } 

};

int main() {
  /* int n, m, s; */
  /* std::cin >> n >> m; */
  /* vector<vector<int> > adj(n, vector<int>()); */
  /* vector<vector<int> > cost(n, vector<int>()); */
  /* for (int i = 0; i < m; i++) { */
  /*   int x, y, w; */
  /*   std::cin >> x >> y >> w; */
  /*   adj[x - 1].push_back(y - 1); */
  /*   cost[x - 1].push_back(w); */
  /* } */
  /* std::cin >> s; */
  /* s--; */
  vector<long long> distance;
  vector<int> reachable;
  vector<int> shortest;
  Directed_Graph graph;
  graph.Data_Read();
  graph.shortest_paths(distance, reachable, shortest);
  for (int i = 0; i < distance.size(); i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
