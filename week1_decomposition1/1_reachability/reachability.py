#Uses python3

import sys

class Undirected_Graph:
    def __init__(self, adjacency_list_):
        self.adjacency_list = adjacency_list_

    def explore(self, v, visited):
       visited[v] = True

       for i in range(len(self.adjacency_list[v])):
           w = self.adjacency_list[v][i]
           if not visited[w]:
               self.explore(w, visited)

    def reach(self, x, y):
        visited = [False] * len(self.adjacency_list)
        self.explore(x, visited)
        if visited[y] == True:
            return 1
        else:
            return 0

if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    x, y = data[2 * m:]
    adj = [[] for _ in range(n)]
    x, y = x - 1, y - 1
    for (a, b) in edges:
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)

    graph = Undirected_Graph(adj)
    print(graph.reach(x, y))
