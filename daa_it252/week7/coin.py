#!/usr/bin/env python

def sol(n, coins):
    finalNumber = float('inf')
    coins.sort(reverse=True)
    val = n
    while coins != []:
        number = 0
        n = val
        for coin in coins:
            if n >= coin:
                number += n/coin
                n %= coin
        finalNumber = min(finalNumber, number)
        coins.remove(coins[0])
    return finalNumber

def main():
    coins = [int(x) for x in raw_input("Enter coins: ").split()]
    n = input("Enter value: ")
    print "Min coins",sol(n, coins)

if __name__ == '__main__':
    main()
