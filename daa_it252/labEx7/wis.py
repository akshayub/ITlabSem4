#!/usr/bin/env python

a = [(2, 4, 8),
     (0, 3, 10),
     (1, 5, 6),
     (3, 6, 4)]

dp = [-1] * len(a)
job = []

def prev(a,i):
    start = a[i][0]
    for x in range(i-1,-1,-1):
        if start >= a[x][1]:
            return x
    return -1

def max_opt_wt(a,i):
    if i == -1:
        return 0
    elif dp[i] != -1:
        return dp[i]
    else:
        dp[i] = max(max_opt_wt(a, i-1), a[i][2] + max_opt_wt(a, prev(a,i)))
        return dp[i]

def print_soln(a,i):
    if i == -1:
        return None
    if a[i][2] + dp[prev(a,i)] > dp[i-1]:
        print a[i]
        print print_soln(a,prev(a,i))
    else:
        print a[i]
        print print_soln(a,i-1)

b = sorted(a, key = lambda x: x[1])
print max_opt_wt(b,len(b)-1)
print_soln(b,len(b)-1)
