#Uses python3

import sys


class Directed_Graph:
    def __init__(self):
        self.adj = None
        self.cost = None

    def Data_Read(self):
        input = sys.stdin.read()
        data = list(map(int, input.split()))
        n, m = data[0:2]
        data = data[2:]
        edges = list(zip(zip(data[0:(3 * m):3], data[1:(3 * m):3]), data[2:(3 * m):3]))
        data = data[3 * m:]
        self.adj = [[] for _ in range(n+1)]
        self.cost = [[] for _ in range(n+1)]
        for ((a, b), w) in edges:
            self.adj[a - 1].append(b - 1)
            self.cost[a - 1].append(w)

        '''
            What if the negative cycle is unreachable from the source vertex?
            The simplest approach is to add an extra vertex and add an edge of length 1 from this vertex to each vertex of the initial graph.
            you have to set the source to be the added vertex.
        '''
        for i in range(n):
            self.adj[n].append(i)
            self.cost[n].append(1)

    def is_negative_cycle(self):
        ''' Detect the negative_cycle in the given connected graph.
            Time Complexity: O(|V||E|)
        '''
        dist = [float('inf')] * len(self.adj)
        source = len(self.adj) - 1
        dist[source] = 0

        for k in range(len(self.adj)):  # |V| iterations
            for i in range(len(self.adj)):
                for j in range(len(self.adj[i])):
                    u = i
                    v = self.adj[i][j]
                    w = self.cost[i][j]  # from u to v

                    # check for relaxation
                    # Note that only if u is already relaxed, v can be relaxed.
                    if dist[u] != float('inf') and dist[v] > dist[u] + w:
                        if k == len(self.adj) - 1:
                            return 1

                        dist[v] = dist[u] + w;

        return 0




def negative_cycle(adj, cost):
    #write your code here
    return 0


if __name__ == '__main__':
    graph = Directed_Graph()  # () is necessary but not for C++
    graph.Data_Read()
    print(graph.is_negative_cycle())
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
    # print(negative_cycle(adj, cost))
