#Uses python3

import sys
import queue


class Directed_Graph:
    def __init__(self):
        self.adj = None
        self.cost = None
        self.s = None

    def Data_Read(self):
        input = sys.stdin.read()
        data = list(map(int, input.split()))
        n, m = data[0:2]
        data = data[2:]
        edges = list(zip(zip(data[0:(3 * m):3], data[1:(3 * m):3]), data[2:(3 * m):3]))
        data = data[3 * m:]
        self.adj = [[] for _ in range(n)]
        self.cost = [[] for _ in range(n)]
        for ((a, b), w) in edges:
            self.adj[a - 1].append(b - 1)
            self.cost[a - 1].append(w)
        self.s = data[0]
        self.s -= 1   # convert to zero-based index.

    def shortest_paths(self, dist, reachable, shortest):
        for i in range(len(self.adj)):
            dist.append(float('inf'))
            reachable.append(1)
            shortest.append(1)

        q_neg = queue.Queue()

        dist[self.s] = 0
        for k in range(1, len(self.adj) + 1):  # |V| iterations
            for i in range(len(self.adj)):
                for j in range(len(self.adj[i])):
                    u = i;
                    v = self.adj[i][j]
                    w = self.cost[i][j] # from u to v

                    # Check for relaxation
                    if dist[u] != float('inf') and dist[v] > dist[u] + w:
                        if k == len(self.adj):
                            q_neg.put(v)
                        dist[v] = dist[u] + w

        for i in range(len(self.adj)):
            if dist[i] == float('inf'):
                reachable[i] = 0


        # Do breadth first search find all vertices reachable from q_neg.
        # Dequeu parent and Enqueue child until empty
        while not q_neg.empty():
            u = q_neg.get() # remove and return
            shortest[u] = 0

            # visit children
            for i in range(len(self.adj[u])):
                v = self.adj[u][i]
                if shortest[v]:  # not visited
                    q_neg.put(v)



if __name__ == '__main__':
    graph = Directed_Graph()
    graph.Data_Read()
    distance = []
    reachable = []
    shortest = []
    graph.shortest_paths(distance, reachable, shortest)
    for x in range(len(distance)):
        if reachable[x] == 0:
            print('*')
        elif shortest[x] == 0:
            print('-')
        else:
            print(distance[x])

