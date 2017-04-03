#!/usr/bin/env python

graph = {}
numberOfNodes = input()
for i in xrange(numberOfNodes):
    v = raw_input()
    edges = list(raw_input().split())
    weights = map(int, list(raw_input().split()))
    graph[v] = dict(zip(edges, weights))

nodes = graph.keys()
distances = graph
unvisited = {node: None for node in nodes}
visited = {}
current = 'a'
currentDistance = 0
unvisited[current] = currentDistance

while True:
    for neighbour, distance in distances[current].items():
        if neighbour not in unvisited: continue
        newDistance = currentDistance + distance
        if unvisited[neighbour] is None or unvisited[neighbour] > newDistance:
            unvisited[neighbour] = newDistance
    visited[current] = currentDistance
    del unvisited[current]
    if not unvisited: break
    candidates = [node for node in unvisited.items() if node[1]]
    current, currentDistance = sorted(candidates, key = lambda x: x[1])[0]

print(visited)
