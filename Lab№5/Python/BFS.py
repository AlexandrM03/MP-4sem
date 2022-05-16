graph = {
  '0' : ['2'],
  '1' : [],
  '2' : ['3', '5'],
  '3' : ['1', '4', '5', '6'],
  '4' : ['1', '6'],
  '5' : ['6'],
  '6' : []
}

visited = []
queue = [] 

def bfs(visited, graph, node):
  visited.append(node)
  queue.append(node)

  while queue:
    s = queue.pop(0) 
    print (s, end = " ") 

    for neighbour in graph[s]:
      if neighbour not in visited:
        visited.append(neighbour)
        queue.append(neighbour)

bfs(visited, graph, '0')