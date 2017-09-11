#!/usr/bin/python
# -*- coding: cp1251 -*-
#
# Author: Yaroslav Pogrebnyak (yyyaroslav@gmail.com)
# http://bitsofmind.wordpress.com
#

# Символ для значения нейрона
dict = { -1 : '-', 1 : '@' }
def charfor(x):
    return dict[x]

#
# Печатает образ в виде ASCII-графики
#
def printshape(obraz, size):
    i = 0
    for o in obraz:
        print "%s" % ( charfor(o) ),
        i+=1
        if i % size == 0: print

