#!/usr/bin/env python
from time import time
count = 0
iterations = 0

def mergesort(b,l,r):
    if l < r:
        m = l + (r - l) / 2;
        mergesort(b,l,m)
        mergesort(b,m+1,r)
        merge(b,l,m,r)

def merge(b,l, m, r):
    global count, iterations
    temp1 = []
    temp2 = []
    s1 = m-l+1
    s2 = r-m

    for i in range(s1):
        iterations += 1
        temp1.append(b[l+i])
    for j in range(s2):
        iterations += 1
        temp2.append(b[m+1+j])

    k = l
    i,j = 0,0

    while i<s1 and j < s2:
        iterations += 1
        if temp1[i] <= temp2[j]:
            b[k] = temp1[i]
            i+=1
        else:
            b[k] = temp2[j]
            j+=1
            count+=s1-i
        k+=1

    while i < s1:
        iterations += 1
        b[k] = temp1[i]
        i+=1
        k+=1

    while j < s2:
        iterations += 1
        b[k] = temp2[j]
        j+=1
        k+=1

def main():
    a = [int(x) for x in raw_input("Enter the array elements: ").split()]
    start = time()
    mergesort(a,0,len(a)-1)
    end = time()
    # print "Number of inversions:",count
    print "Inversions : %d \n Iterations : %d" %(count, iterations)
    print "Real Time taken : ", end-start

if __name__ == '__main__':
    main()
