#Uses python3
import sys
import math

class Disjoint_Sets_Element:
    def __init__(self, _parent = -1, _rank = 0):
        self.parent = _parent
        self.rank = _rank

class Disjoint_Sets:
    '''
    Disjoint Sets support the following operations:
    make_set(x): creates a singleton set {x}
    find(x): returns ID of the set containing x
    union(x, y): merges two sets containing x and y,respectively.
    '''
    def __init__(self, _size):
        '''
        Implement the Make_Set to create singleton sets
        '''
        self.sets = [Disjoint_Sets_Element(i, 0) for i in range(_size)]
        self.size = _size
        self.num_of_sets = _size;

    def find(self, i):
        while i != self.sets[i].parent:
            i = self.sets[i].parent

        return i

    def merge(self, i, j):
        i_id = self.find(i);
        j_id = self.find(j);

        if i_id == j_id:
            return
        elif self.sets[i_id].rank < self.sets[j_id].rank:
            self.num_of_sets -= 1
            self.sets[i_id].parent = j_id
        else:
            self.num_of_sets -= 1
            self.sets[j_id].parent = i_id

            if self.sets[i_id].rank == self.sets[j_id].rank:
                self.sets[i_id].rank += 1

    def print_state(self):
        print("parent")
        for i in range(self.size):
            print(f'{self.sets[i].parent} ', end='')

        print('\n')


        print("rank")
        for i in range(self.size):
            print(f'{self.sets[i].rank} ', end='')

        print('\n')

class Edge:
    def __init__(self, _pt1, _pt2, _len):
        self.end_point_one = _pt1
        self.end_point_two = _pt2
        self.length = _len;

class Point_Set:
    def __init__(self):
        self.size = None
        self.edges = None
        self.x = None
        self.y = None

    def Data_Read(self):
        input = sys.stdin.read()
        data = list(map(int, input.split()))
        n = data[0]
        x = data[1::2]
        y = data[2::2]
        self.x = x
        self.y = y
        self.size = n
        self.edges = []
        for i in range(n):
            for j in range(i+1, n):
                self.edges.append(Edge(i, j, self.compute_distance(x[i], y[i], x[j], y[j])))

    def compute_distance(self, x1, y1, x2, y2):
        return math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))


    def Kruskal_MST(self):
        dis_sets_vertices = Disjoint_Sets(self.size)
        result_mst = []
        self.edges.sort(key = lambda x : x.length)  # sorting the edges in ascending order of the edge length.

        for i in range(len(self.edges)):
            u = self.edges[i].end_point_one;
            v = self.edges[i].end_point_two;
            if dis_sets_vertices.find(u) != dis_sets_vertices.find(v):
                # If u and v not in the same set, then edge joining them is impossible to produce a cycle.

                result_mst.append(Edge(self.edges[i].end_point_one,
                                       self.edges[i].end_point_two,
                                       self.edges[i].length))
                # You can instantiate an class using a object of the same class like c++
                dis_sets_vertices.merge(u, v)


        minimum_distance = 0
        for i in range(len(result_mst)):
            minimum_distance += result_mst[i].length

        return minimum_distance

#def minimum_distance(x, y):
#    result = 0.
#    #write your code here
#    return result


if __name__ == '__main__':
    # input = sys.stdin.read()
    # data = list(map(int, input.split()))
    # n = data[0]
    # x = data[1::2]
    # y = data[2::2]
    point_set = Point_Set();
    point_set.Data_Read();
    print("{0:.9f}".format(point_set.Kruskal_MST()))
