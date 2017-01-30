#!/usr/bin/env python
# for numerical vertices numbered from 1-n
# taking input of edges

n = input()
graph={}

for i in range(1,n+1):
    graph[str(i)] = []

print 'enter edges'

for i in range(n):
    edge = raw_input()
    v1,v2=list(edge)
    graph[v1].append(v2)
    graph[v2].append(v1)    # comment line for undirect edges

print graph
