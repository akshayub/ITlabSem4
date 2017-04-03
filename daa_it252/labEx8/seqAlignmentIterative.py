#!/usr/bin/env python
import sys

def findEdit(x,y):
    dp = []

    for i in range(len(x)+1):
        sub = []
        for j in range(len(y)+1):
            sub.append(999)
        dp.append(sub)

    for i in range(len(x),-1,-1):
        for j in range(len(y),-1,-1):
            if i == len(x):
                dp[i][j] = len(y) - j
                continue
            if j == len(y):
                dp[i][j] = len(x) - i
                continue

            if x[i] != y[j]:
                diff = 1
            else:
                diff = 0

            p1 = diff + dp[i+1][j+1]
            p2 = 1 + dp[i][j+1]
            p3 = 1 + dp[i+1][j]

            dp[i][j] = min(p1,p2,p3)

    print dp[0][0]

if len(sys.argv) != 3:
    sys.stderr.write("Usage: {0} <String1> <String2>\n".format(sys.argv[0]))
    exit(-1)
findEdit(sys.argv[1], sys.argv[2])
