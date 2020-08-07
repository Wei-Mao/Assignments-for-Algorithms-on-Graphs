#Uses python3
# Remarks:
# Python's built-in List data structure comes bundled with methods to simulate both stack and queue operations.
# Reference at https://docs.python.org/2/tutorial/datastructures.html
# To implement a queue, use collections.deque which was designed to have fast appends and pops from both ends


import sys

sys.setrecursionlimit(200000)

class Directed_Graph:
    def __init__(self):
        self.adjacency_list = None
        self.adjacency_list_reverse = None

    def data_read(self):
        input = sys.stdin.read()
        data = list(map(int, input.split()))
        n, m = data[0:2]
        # [[element] * numcols] * numrows must specify the num cols. otherwise numcols becomes the same
        # When you do [None] * n, Python internally creates a list object of size n and it copies the the same object
        # (here None) (this is the reason, you should use this method only when you are dealing with immutable objects) to all the memory locations.
        # adj = [[] for _ in range(n)], numcols is variable.
        self.adjacency_list = [[] for _ in range(n)]
        self.adjacency_list_reverse = [[] for _ in range(n)]
        data = data[2:]
        edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
        adj = [[] for _ in range(n)]
        for (a, b) in edges:
            self.adjacency_list[a - 1].append(b - 1)
            self.adjacency_list_reverse[b - 1].append(a - 1)
            # The index of the first dimension of the 2D corresponds to the vertex number.
            # Both for original and reverse Adj. List representation.

    def explore(self, v, adj_list, vertex_status, is_cycle, stack_order):
        ''' Check whether there is a cycle containing vertex v.
            Input:
                v(int): Zero-based index for the given vertex.
                adj_list: Adjacency List of the original or reverse version
                vertex_status(vector<string>): "unvisited" if vertex has not been visited yet;
                                "begin" if explore(v) has started;
                                "end" if explore(v) has terminated.
                is_cycle(bool): true if detecting a cycle.
                stack_order(stack<int>): store the vertex numbers in linear order.
                Namely, for edge (u, v), u must show up before v.
            Output:Void.
            Time Complexity: O(# of edges in in the  visited subgraph)
            Space Complexity: O(1). We takes the reference to vector as input.
            Remark: Reference at https://stackoverflow.com/questions/261573/best-algorithm-for-detecting-cycles-in-a-directed-graph
        '''
        vertex_status[v] = "begin"
        for i in range(len(adj_list[v])):
            w = adj_list[v][i]

            if vertex_status[w] == "begin":
                is_cycle[0] = True

            if vertex_status[w] == "unvisited":
                self.explore(w, adj_list,  vertex_status, is_cycle, stack_order)

        vertex_status[v] = "end"
        stack_order.append(v)

    def is_cycle_DFS(self):
        ''' Check whether the graph contains a graph by detecting the back edge.
            Time Complexity: O(|V| + |E|)
            Space Complexity: O(|V|)
        '''
        vertex_status = ["unvisited"] * len(self.adjacency_list)
        # is_cycle = False bool is not mutable
        # The only way around this is to pass a mutable object. Because both references refer to the same object,
        # any changes to the object are reflected in both places.
        # Passing mutable object in python amounts to passing by reference in C++
        # Otherwise, Python will create a new reference.
        is_cycle = [False]
        stack_order = []

        for v in range(len(self.adjacency_list)):
            if vertex_status[v] == "unvisited":
                self.explore(v, self.adjacency_list, vertex_status, is_cycle, stack_order)

        res = 1 if is_cycle[0] else 0
        return res

    def topological_sort(self):
        ''' Linearly order the directed graph.

            A topological sort of a DAG G=(V, E) is a linear ordering of all
            its vertices such that if G contains an edge (u,v), then u appers before v in the ordering.
            Algorithm: Call DFS(G) to compute postorder number.
            As each vertex is finished, insert it to the stack(Last In First Out).
            Time Complexity: O(|V| + |E|)
            Space Complexity: O(|V|)
        '''
        vertex_status = ["unvisited"] * len(self.adjacency_list)
        # is_cycle = False bool is not mutable
        # The only way around this is to pass a mutable object. Because both references refer to the same object,
        # any changes to the object are reflected in both places.
        # Passing mutable object in python amounts to passing by reference in C++
        # Otherwise, Python will create a new reference.
        is_cycle = [False]
        stack_order = []

        for v in range(len(self.adjacency_list)):
            if vertex_status[v] == "unvisited":
                self.explore(v, self.adjacency_list, vertex_status, is_cycle, stack_order)

        return stack_order

    def DFS(self, adj_list):
        '''Depth First Search on the Original Graph.

           Input:
               adj_list: the Adjacency List of the Original or Reverse Graph.
           Return the reversed linear order, ignoring the cycle.
        '''
        vertex_status = ["unvisited"] * len(adj_list)
        # is_cycle = False bool is not mutable
        # The only way around this is to pass a mutable object. Because both references refer to the same object,
        # any changes to the object are reflected in both places.
        # Passing mutable object in python amounts to passing by reference in C++
        # Otherwise, Python will create a new reference.
        is_cycle = [False]
        stack_order = []

        for v in range(len(adj_list)):
            if vertex_status[v] == "unvisited":
                self.explore(v, adj_list, vertex_status, is_cycle, stack_order)

        return stack_order

    def num_sccs(self):
        '''Compute the number of strongly connected components(SCC) in the graph.

           Return: The number SCCs
           Time Complexity:O(|V| + |E|)
           Space Complexity:O(|V|)
        '''
        post_order = []
        post_order = self.DFS(self.adjacency_list_reverse)
        vertex_status = ["unvisited"] * len(self.adjacency_list)
        is_cycle = [False]
        stack_order = []
        number_of_SCCs = 0
        while post_order: # empty list evaluates to false.
            v = post_order.pop()  # return and remove
            if vertex_status[v] == "unvisited":
                self.explore(v, self.adjacency_list, vertex_status, is_cycle, stack_order)
                number_of_SCCs = number_of_SCCs + 1

        return number_of_SCCs

if __name__ == '__main__':
    graph = Directed_Graph()
    graph.data_read()
    print(graph.num_sccs())

    # input = sys.stdin.read()
    # data = list(map(int, input.split()))
    # n, m = data[0:2]
    # data = data[2:]
    # edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    # adj = [[] for _ in range(n)]
    # for (a, b) in edges:
    #     adj[a - 1].append(b - 1)
    # print(number_of_strongly_connected_components(adj))
