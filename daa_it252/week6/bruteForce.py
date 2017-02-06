#!/usr/bin/env python
from time import time
a = [int(x) for x in raw_input("Enter the array elements: ").split()]
# print "The number of inversion:",sum([1 for x in range(len(a)) for y in range(x,len(a)) if a[x] > a[y]])
count = 0
iterations = 0
start = time()
for x in range(len(a)):
    for y in range(x,len(a)):
        iterations += 1
        if a[x] > a[y]:
            count += 1
end = time()
print "Inversions : %d \n Iterations : %d" %(count, iterations)
print "Real Time taken : ", end-start
