#Uses python3

import sys

class Directed_Graph:
    def __init__(self, adjacency_list_):
        self.adjacency_list = adjacency_list_

    def explore(self, v, vertex_status, is_cycle):
        ''' Check whether there is a cycle containing vertex v.
            Input:
                v(int): Zero-based index for the given vertex.
                vertex_status(vector<string>): "unvisited" if vertex has not been visited yet;
                                "begin" if explore(v) has started;
                                "end" if explore(v) has terminated.
                is_cycle(bool): true if detecting a cycle.
            Output:Void.
            Time Complexity: O(# of edges in in the  visited subgraph)
            Space Complexity: O(1). We takes the reference to vector as input.
            Remark: Reference at https://stackoverflow.com/questions/261573/best-algorithm-for-detecting-cycles-in-a-directed-graph
        '''
        vertex_status[v] = "begin"
        for i in range(len(self.adjacency_list[v])):
            w = self.adjacency_list[v][i]

            if vertex_status[w] == "begin":
                is_cycle[0] = True

            if vertex_status[w] == "unvisited":
                self.explore(w, vertex_status, is_cycle)

        vertex_status[v] = "end"

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

        for v in range(len(self.adjacency_list)):
            if vertex_status[v] == "unvisited":
                self.explore(v, vertex_status, is_cycle)

        res = 1 if is_cycle[0] else 0
        return res

if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    adj = [[] for _ in range(n)]
    for (a, b) in edges:
        adj[a - 1].append(b - 1)
    graph = Directed_Graph(adj)
    print(graph.is_cycle_DFS())
