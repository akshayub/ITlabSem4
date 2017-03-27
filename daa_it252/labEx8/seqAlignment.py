#!/usr/bin/env python
from sys import argv

def diff(x,y):
    if x == y:
        return 0
    else:
        return 1

def findEdit(x,i,y,j):
    if i < len(x) and j < len(y):
        ans1 = diff(x[i], y[j]) + findEdit(x,i+1,y,j+1)
        ans2 = diff(x[i], None) + findEdit(x,i+1,y,j)
        ans3 = diff(None, y[j]) + findEdit(x,i,y,j+1)
        ans = min(ans1, ans2, ans3)
        return ans
    else:
        return 0

print "Cost is ", findEdit(argv[1], 0, argv[2], 0)
