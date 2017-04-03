#!/usr/bin/env python
import sys

def findEdit(x,i,y,j):
    if i == 0:
        return j
    elif j == 0:
        return i

    if x[i-1] == y[j-1]:
        return findEdit(x, i-1, y, j-1)
    
    return 1 + min(findEdit(x,i,y,j-1), findEdit(x,i-1,y,j), findEdit(x,i-1,y,j-1))

if len(sys.argv) != 3:
    sys.stderr.write("Usage: {0} <String1> <String2>\n".format(sys.argv[0]))
    exit(-1)
print "Cost is \n", findEdit(sys.argv[1], len(sys.argv[1]), sys.argv[2], len(sys.argv[1]))
