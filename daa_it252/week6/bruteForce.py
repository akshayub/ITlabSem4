#!/usr/bin/env python
a = [int(x) for x in raw_input("Enter the array elements: ").split()]
print "The number of inversion:",sum([1 for x in range(len(a)) for y in range(x,len(a)) if a[x] > a[y]])
