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
    global time,t,color,parent
    time += 1
    t[u] = time
    color[u] = "GREY"
    for v in g[u]:
        if color[v] == "WHITE":
            parent[v] = u
            dfs_visit(g,v)
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
    # color[v] = "WHITE"
    # parent[v] = "NIL"
    # t[v] = 0
    # graph[v] = set(raw_input('List of vertices? ').strip(' ').split())
    graph[v] = list(set((f.readline().replace('\n','')).strip(' ').split()))
    for j in graph[v]:
        # edges.append(''.join([str(i+1),j]))
        edges[''.join([str(i+1),j])] = ""
print "Edges: ", edges.keys()
print "\nGraph is \n" , graph, "\n\nDFS Traversal"
dfs(graph)
f.close()
