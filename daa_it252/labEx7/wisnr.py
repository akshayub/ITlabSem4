#!/usr/bin/env python

a = [(2, 4, 8),
     (0, 3, 10),
     (1, 5, 6),
     (3, 6, 4)]

dp = [0] * len(a)
prevdp = [0] * len(a)
job = []

def prev(a,i):
    if i == -1:
        return 0
    start = a[i][0]
    if prevdp[i] == 0:
        for x in range(i-1,-1,-1):
            if start >= a[x][1]:
                prevdp[i] = x
                break
        else:
            return -1
    return prevdp[i]

def opt_wt(a):
    for j in range(len(a)):
        if j == 0:
            dp[0] = a[0][2]
        else:
            dp[j] = max(a[j][2] + dp[prev(a,j)], dp[j-1])
    print dp[len(a)-1]

def print_soln(a,i):
    if i == -1:
        return ''
    if a[i][2] + dp[prev(a,i)] > dp[i-1]:
        print a[i]
        print print_soln(a,prev(a,i))
    else:
        print print_soln(a,i-1)

b = sorted(a, key = lambda x: x[1])
print b
opt_wt(b)
print_soln(b,len(b)-1)
