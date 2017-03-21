#!/usr/bin/env python
from math import isinf
# This is incomplete
def sol(val, coins):
    if val == 0:
        return 0
    ans = float('inf')
    for coin in coins:
        if coin < val:
            res = sol(val - coin, coins)
            if not isinf(res) and res + 1 < ans:
                ans = res + 1
    return ans

def main():
    coins = [int(x) for x in raw_input("Enter coins: ").split()]
    coins.sort(reverse=True)
    n = input("Enter value: ")
    print "Min coins", sol(n, coins)

if __name__ == '__main__':
    main()
