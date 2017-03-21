#!/usr/bin/env python
coinsCount = {}
def sol(n, coins):
    global coinsCount
    finalNumber = float('inf')
    coins.sort(reverse=True)
    val = n
    while coins != []:
        number = 0
        n = val
        temp = {}
        for coin in coins:
            if n >= coin:
                number += n/coin
                temp[coin] = n/coin
                n %= coin
        if min(finalNumber, number) == number:
            coinsCount = dict(temp)
        finalNumber = min(finalNumber, number)
        coins.remove(coins[0])
    return finalNumber

def main():
    coins = [int(x) for x in raw_input("Enter coins: ").split()]
    n = input("Enter value: ")
    print "Min coins",sol(n, coins)
    # print coinsCount
    for coin in coinsCount:
        print 'Coin of value', coin, 'used ', coinsCount[coin], 'times'

if __name__ == '__main__':
    main()
