from collections import defaultdict
  
class Graph:
    def __init__(self,vertices):
        self.graph = defaultdict(list)
        self.V = vertices
  
    def addEdge(self,u,v):
        self.graph[u].append(v)
  
    def topologicalSortUtil(self,v,visited,stack):
  
        visited[v] = True
  
        for i in self.graph[v]:
            if visited[i] == False:
                self.topologicalSortUtil(i,visited,stack)
  
        stack.insert(0,v)
  
    def topologicalSort(self):
        visited = [False]*self.V
        stack = []
  
        for i in range(self.V):
            if visited[i] == False:
                self.topologicalSortUtil(i,visited,stack)
  
        print (stack)
  
g = Graph(7)
g.addEdge(0, 2);
g.addEdge(2, 3);
g.addEdge(2, 5);
g.addEdge(3, 1);
g.addEdge(3, 4);
g.addEdge(3, 5);
g.addEdge(3, 6);
g.addEdge(4, 1);
g.addEdge(4, 6);
g.addEdge(5, 6);
  
print ("Following is a Topological Sort of the given graph")
g.topologicalSort()


