#Uses python3

import sys
import queue

class Undirected_Graph:
    def __init__(self):
        self.adj = None
        self.s = None
        self.t = None

    def Data_Read(self):
        input = sys.stdin.read()
        data = list(map(int, input.split()))
        n, m = data[0:2]
        data = data[2:]
        edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
        self.adj = [[] for _ in range(n)]
        for (a, b) in edges:
            self.adj[a - 1].append(b - 1)
            self.adj[b - 1].append(a - 1)
        self.s, self.t = data[2 * m] - 1, data[2 * m + 1] - 1

    def BFS(self, S):
        ''' Breadth-First Search on the Directed_Graph
            Input:
                S(int): Index of the specified origin (zero-based).
            Return:
                vector<int>. The vector of distances from all vertices to the origin S.
            Time Complexity: O(|V| + |E|)
            Space Complexity: O(|V|)
        '''
        num_of_vertices = len(self.adj)
        dist = [num_of_vertices] * num_of_vertices;
        dist[S] = 0
        queue_vertex = queue.Queue()
        queue_vertex.put(S)

        while not queue_vertex.empty():
            u = queue_vertex.get()
            for i in range(len(self.adj[u])):
                v = self.adj[u][i]
                if dist[v] == num_of_vertices:
                    queue_vertex.put(v)
                    dist[v] = dist[u] + 1

        return dist

    def compute_distance(self, u, v):
        ''' Compute the distance from u to v.

            Input:
                u and v are the index of the two vertices. (zero-based)
            Return:
                The distance between them if there is a path between them. Otherwise, -1.
        '''
        dist = self.BFS(u)

        return dist[v] if dist[v] != len(self.adj) else -1

    def process(self):
        return self.compute_distance(self.s, self.t)

if __name__ == '__main__':
    graph = Undirected_Graph()
    graph.Data_Read()
    print(graph.process())

    # input = sys.stdin.read()
    # data = list(map(int, input.split()))
    # n, m = data[0:2]
    # data = data[2:]
    # edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    # adj = [[] for _ in range(n)]
    # for (a, b) in edges:
    #     adj[a - 1].append(b - 1)
    #     adj[b - 1].append(a - 1)
    # s, t = data[2 * m] - 1, data[2 * m + 1] - 1
    # print(distance(adj, s, t))
