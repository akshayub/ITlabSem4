#!/usr/bin/env python
from sys import argv

def dfs(g):
    global color,parent
    for u in g.keys():
        color[u] = "WHITE"
        parent[u] = "NIL"
    # time = 0   # Coz it's used globally, I defined time outside
    for u in g.keys():
        if color[u] == "WHITE":
            dfs_visit(g,u)

def dfs_visit(g,u):
    global time,t,color,parent, edges
    time += 1
    t[u] = time
    color[u] = "GREY"
    for v in g[u]:
        if color[v] == "WHITE":
            parent[v] = u
            edges[''.join([u,v])] = "Tree"
            dfs_visit(g,v)
        if parent[v] != u and color[v] == "GREY":
            edges[''.join([u,v])] = "Back"
        # elif parent[v] != u:
        #     print "bleh",u,v, parent[v], color[u], color[v], t[u], t[v]
    color[u] = "BLACK"
    print u
    time += 1
    t[u] = time

# n = input("Number of nodes in the graph   ")
if len(argv) == 1:
    print "Enter input filename as commandline argument"
    exit()
else:
    f = open(argv[1],"r")
graph = {}
color = {}
parent = {}
t = {}
edges = {}
time = 0
# print 'Enter adjacency list'
n = int((f.readline().replace('\n','')))
for i in xrange(n):
    # v = raw_input('Vertex? ')
    v = (f.readline().replace('\n',''))

    # graph[v] = set(raw_input('List of vertices? ').strip(' ').split())
    graph[v] = list(set((f.readline().replace('\n','')).strip(' ').split()))
    graph[v].sort()

    for j in graph[v]:
        # edges.append(''.join([str(i+1),j]))
        edges[''.join([str(i+1),j])] = ""

print "\nGraph is \n" , graph, "\n\nDFS Traversal"
dfs(graph)
f.close()
print "\nEdges:\n", edges
