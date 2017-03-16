#!/usr/bin/env python

# Top down approach for getting max weight of all non-overlapping intervals.
# By the method of Dynamic programming.

class Interval(object):
    start = 0
    end = 0
    weight = 0
    def __init__(self, vals):
        self.start = vals[0]
        self.end = vals[1]
        self.weight = vals[2]

def getPrev(intervals):
    ans = [None] * len(intervals)
    starts = map(lambda x:x.start, intervals)
    ends = map(lambda x:x.end, intervals)
    weights = map(lambda x:x.weight, intervals)
    for x in xrange(len(intervals)-1,-1,-1):
        try:
            print intervals[x].end
        except Exception:
            ans[x] = None
    return ans

def optimalSol(intervals, prevs):
    ans = 0
    pass
    print prevs
    return ans


def main():
    # intervals = input("Number of intervals? ")
    intervals = input()
    allIntervals = []
    # print 'Enter start, end, weight of intervals'
    for interval in xrange(intervals):
        # start, end, weight = [int(x) for x in raw_input().split()]
        allIntervals.append(
            Interval(
                [int(x) for x in raw_input().split()]
            )
        )
    allIntervals.sort(key = lambda x:x.end)

    print optimalSol(allIntervals, getPrev(allIntervals))

if __name__ == '__main__':
    main()
