def dfs(graph, start, visited=None):
    if visited is None:
        visited = set()
    visited.add(start)
    print start
    for next in graph[start]-visited:
        dfs(graph, next, visited)
    return visited

def main():
    n = input("Number of nodes in the graph   ")
    graph = {}
    print 'Enter adjacency list'
    for i in xrange(n):
        v = raw_input('Vertex? ')
        graph[v] = set(raw_input('List of vertices? ').strip(' ').split())
    print graph
    dfs(graph, graph.keys()[0])

if __name__ == '__main__':
    main()
