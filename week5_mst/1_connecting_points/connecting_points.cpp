#include <algorithm>  // std::sort
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using std::vector;

class Disjoint_Sets_Element 
{
  public:
    // Element represents an original single element.
    int parent, rank;

    // constuctor
    Disjoint_Sets_Element(int parent = -1, int rank = 0)
      :parent(parent), rank(rank)
    {}
};

class Disjoint_Sets 
{
   /* Disjoint Sets support the following operations: */
   /* make_set(x): creates a singleton set {x} */
   /* find(x): returns ID of the set containing x */
   /* union(x, y): merges two sets containing x and y,respectively. */
  public:
    vector<Disjoint_Sets_Element> sets;  // singleton set, one for one element
    int size;
    int num_of_sets;

    // constuctor. Implement the maks_set to create singleton sets
    // Make_Set(i)
    Disjoint_Sets(int _size)
      :size(_size), num_of_sets(_size)
    {
      sets.resize(_size);
      for(int i(0); i < _size; i++)
      {
	sets[i].parent = i;  // root of singleton set is itself
	sets[i].rank = 0;    // one node tree is of zero height.
      }
    }
    
    int find(int i)
    {
      /* Return the ID of the set i belongs to.
	 Input:
	      i(int):  the index of the element of interest.
	 Return: the ID of the set containing element indexed by i
      */
      while(i != sets[i].parent)
      {
	i = sets[i].parent;
      }

      return i; // root index as the set ID
    }

    void merge(int i, int j)
    {
      /* Merging sets containing elements indexed by i and j.
	 Input:
	      i and j: the index of the two elements.
      */

      int i_id = find(i);
      int j_id = find(j);

      if (i_id == j_id)
      {
	// the given two elements already lie in the same set
	return;
      } else if (sets[i_id].rank < sets[j_id].rank)
      {
	num_of_sets --;
	// set containing i is shorter than set containing j
	// Hang a shorter tree under the root of the taller one, aka union by rank heuristic
	// update the parent of the root of the shorter to be the root of the taller.
	// rank of nodes in the shorter one is preserved.
	sets[i_id].parent = j_id;
      } else
      {
	num_of_sets--;
	// set containing i is taller than or as high as the one containing j.
	sets[j_id].parent = i_id;
	if (sets[i_id].rank == sets[j_id].rank)
	{
	  // increased the height of the tree to which a tree of the same height is attached.
	  sets[i_id].rank ++;
	}
      }
    }

    void print_state()
    {
      std::cout << "parent" << std::endl;
      for(int i(0); i < size; i++)
      {
	std::cout << sets[i].parent << " ";
      }
      std::cout << std::endl;

      std::cout << "rank" << std::endl;
      for(int i(0); i < size; i++)
      {
	std::cout << sets[i].rank << " ";
      }
      std::cout << std::endl;
    }
};

class Edge 
{
  /* Undirected Edge*/
  public:
    int end_point_one;
    int end_point_two;
    double length;
    
    Edge(int _pt1, int _pt2, double _len)
      :end_point_one(_pt1), end_point_two(_pt2), length(_len)
    {
    }
};

bool compare_edge(Edge &edge1, Edge &edge2)
{
  return edge1.length <= edge2.length;
}

class Point_Set 
{
  private:
    int size;
    vector<Edge> edges;
    vector<int> x;
    vector<int> y;

  public:
    void Data_Read()
    {
      size_t n;
      std::cin >> n;
      size = n;
      /* vector<int> x(n), y(n); */
      x.resize(n);
      y.resize(n);
      for (size_t i = 0; i < n; i++) {
	std::cin >> x[i] >> y[i];
      }

      /* int num_of_edges = n * (n -1) /2; // n choose 2 */
      for(int i(0); i < n; i++)
	for(int j(i + 1); j < n; j++)
	{
	   edges.push_back(Edge(i, j, compute_distance(x[i], y[i], x[j], y[j])));
	}
    }

    double compute_distance(int _x_1, int _y_1, int _x_2, int _y_2)
    {
      double x1 = double(_x_1);
      double y1 = double(_y_1);
      double x2 = double(_x_2);
      double y2 = double(_y_2);
      return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }

    double Kruskal_MST()
    {
      // creates disjoint sets for all vertices
      Disjoint_Sets dis_sets_vertices(size);
      vector<Edge> result_mst;

      // sort the edges by non-descending order of length.
      std::sort(edges.begin(), edges.end(), compare_edge); 

      for(int i(0); i < edges.size(); i++)
      {
	int u = edges[i].end_point_one;
	int v = edges[i].end_point_two;
	if(dis_sets_vertices.find(u) != dis_sets_vertices.find(v))
	{
	  // If u and v not in the same set, then edge joining them is impossible to produce a cycle.
	  /* std::cout << "Before merge IDs " << dis_sets_vertices.find(u) << " and "<< dis_sets_vertices.find(v) << std::endl; */

	  result_mst.push_back(Edge(edges[i]));
	  dis_sets_vertices.merge(u, v);
	  /* std::cout << "After merge IDs " << dis_sets_vertices.find(u) << " and "<< dis_sets_vertices.find(v) << std::endl; */
	}
      }

      double minimum_distance(0);
      for(int i(0); i < result_mst.size(); i++)
      {
	minimum_distance += result_mst[i].length;
      }
      return minimum_distance;
    }
}; 

int main() {
  Point_Set point_set;
  point_set.Data_Read();
  std::cout << std::fixed << std::setprecision(10) << point_set.Kruskal_MST() << std::endl;

  /* size_t n; */
  /* std::cin >> n; */
  /* vector<int> x(n), y(n); */
  /* for (size_t i = 0; i < n; i++) { */
  /*   std::cin >> x[i] >> y[i]; */
  /* } */
  /* std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl; */
}
