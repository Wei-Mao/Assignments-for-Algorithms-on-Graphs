#Uses python3

import sys
import queue
import heapq as pq

class Vertex:
    def __init__(self, _ID, _dist):
        self.ID = _ID
        self.dist = _dist

    def __lt__(self, other):
        return self.ID < other.ID # smaller ID has higher Priority

class Directed_Graph:
    def __init__(self):
        self.adj_list = None
        self.cost = None
        self.s = None
        self.t = None

    def Data_Read(self):
        input = sys.stdin.read()
        data = list(map(int, input.split()))
        n, m = data[0:2]
        data = data[2:]
        edges = list(zip(zip(data[0:(3 * m):3], data[1:(3 * m):3]), data[2:(3 * m):3]))
        data = data[3 * m:]
        self.adj_list = [[] for _ in range(n)]
        self.cost = [[] for _ in range(n)]
        for ((a, b), w) in edges:
            self.adj_list[a - 1].append(b - 1)
            self.cost[a - 1].append(w)
        self.s, self.t = data[0] - 1, data[1] - 1

    def Dijkstra(self, source):
        ''' Dijkstra Algorithm to find the shortest path length with regard to minimum total weights.
            Input:
                source(int): The zero-based index of the source vertex.
            Return:
                Vector of distance from source vertex to all other vertices.
            Remarks: Priority Queue based version.
            Time Complexity: O((|V| + |E|) log|V|)
            Space Complexity: O(|V|)
        '''
        num_of_vertices = len(self.adj_list)
        dist = [float('inf')] * num_of_vertices
        dist[source] = 0
        H = []
        pq.heappush(H, Vertex(source, 0))
        while H:
            u = pq.heappop(H).ID
            for i in range(len(self.adj_list[u])):
                v = self.adj_list[u][i]
                w = self.cost[u][i]

                if dist[v] > dist[u] + w:
                    dist[v] = dist[u] + w
                    pq.heappush(H, Vertex(v, dist[v]))

        return dist

    def process(self):
        dist = self.Dijkstra(self.s)
        return dist[self.t] if dist[self.t] != float('inf') else -1


if __name__ == '__main__':
    graph = Directed_Graph()
    graph.Data_Read()
    print(graph.process())
    # input = sys.stdin.read()
    # data = list(map(int, input.split()))
    # n, m = data[0:2]
    # data = data[2:]
    # edges = list(zip(zip(data[0:(3 * m):3], data[1:(3 * m):3]), data[2:(3 * m):3]))
    # data = data[3 * m:]
    # adj = [[] for _ in range(n)]
    # cost = [[] for _ in range(n)]
    # for ((a, b), w) in edges:
    #     adj[a - 1].append(b - 1)
    #     cost[a - 1].append(w)
    # s, t = data[0] - 1, data[1] - 1
    # print(distance(adj, cost, s, t))
