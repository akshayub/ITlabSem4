#!/usr/bin/env python

from random import randrange as r
from sys import argv

if len(argv) != 2:
    print 'Usage: ./generate.py <NumberOfRandomNumbers>'
else:
    f = open('input','w')
    for i in xrange(int(argv[1])):
        f.write(str(r(-10000,10000)) + " ")
    f.close()
