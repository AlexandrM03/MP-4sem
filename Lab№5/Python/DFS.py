graph = {
  '0' : ['2'],
  '1' : [],
  '2' : ['3', '5'],
  '3' : ['1', '4', '5', '6'],
  '4' : ['1', '6'],
  '5' : ['6'],
  '6' : []
}

visited = set()

def dfs(visited, graph, node):
    if node not in visited:
        print (node, end=' ')
        visited.add(node)
        for neighbour in graph[node]:
            dfs(visited, graph, neighbour)

print("Following is the Depth-First Search")
dfs(visited, graph, '0')


