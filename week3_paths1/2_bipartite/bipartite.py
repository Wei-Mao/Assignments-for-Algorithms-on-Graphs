#Uses python3

import sys
import queue

class Undirected_Graph:
    def __init__(self):
        self.adjacency_list = None

    def Data_Read(self):
        input = sys.stdin.read()
        data = list(map(int, input.split()))
        n, m = data[0:2]
        data = data[2:]
        edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
        self.adjacency_list = [[] for _ in range(n)]
        for (a, b) in edges:
            self.adjacency_list[a - 1].append(b - 1)
            self.adjacency_list[b - 1].append(a - 1)

    def is_bipartite(self):
        '''Assign Color to all vertices, either white or black.

        Return Color Assignments for all vertices.
        Remarks: The breadth-first search in the problem 1 is not a complete version, which only starts from one origin. If you one graph have more than 1 connected component. It will
        not reach the other connected component. BFS(S) is analogous to the explore(S) in the depth-first search. Hence. BFS(S) also finds the connected component of S.
        In other words, the breadth-first search in the video lecture indeed is the one for one connected component. We simply add one external loop to it to consider all connected components. By using markers of visit, we obtain:
        Time Complexity: O(|V| + |E|)
        Of course, you can adapt the depth-first search to check for bipartite.
        '''
        num_of_vertices = len(self.adjacency_list)
        color = [-1] * num_of_vertices
        queue_vertex = queue.Queue()

        for s in range(num_of_vertices):
            if (color[s] == -1):
                # not visited
                queue_vertex.put(s)
                color[s] = 0
                while not queue_vertex.empty():
                    u = queue_vertex.get() # return and remove
                    for i in range(len(self.adjacency_list[u])):
                        v = self.adjacency_list[u][i]

                        if color[v] == -1:
                            # not visited
                            queue_vertex.put(v)
                            color[v] = 1 - color[u]
                        elif color[u] == color[v]:
                            return 0

        return 1



if __name__ == '__main__':
    graph = Undirected_Graph()
    graph.Data_Read()
    print(graph.is_bipartite())
    # input = sys.stdin.read()
    # data = list(map(int, input.split()))
    # n, m = data[0:2]
    # data = data[2:]
    # edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    # adj = [[] for _ in range(n)]
    # for (a, b) in edges:
    #     adj[a - 1].append(b - 1)
    #     adj[b - 1].append(a - 1)
    # print(bipartite(adj))
