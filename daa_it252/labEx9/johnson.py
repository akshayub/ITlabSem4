#!/usr/bin/env python

n = input('no.vertices ')
m = input('no.edges   ')
mat = []
cost = []

for i in range(n):
    mat.append([0]*n)
    cost.append([0]*n)

for k in range(m):
    i,j,c = map(int,raw_input().split())
    mat[i-1][j-1] = cost[i-1][j-1] = c

for i in range(n):
    for j in range(n):
        if mat[i][j] == 0 and i != j:
            mat[i][j] = float('inf')

for k in range(n):
    for i in range(n):
        for j in range(n):
            mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j])

print 'res matrix'
for i in mat:
    print i
