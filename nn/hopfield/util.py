#!/usr/bin/python
# -*- coding: cp1251 -*-
#
# Author: Yaroslav Pogrebnyak (yyyaroslav@gmail.com)
# http://bitsofmind.wordpress.com
#

# ������ ��� �������� �������
dict = { -1 : '-', 1 : '@' }
def charfor(x):
    return dict[x]

#
# �������� ����� � ���� ASCII-�������
#
def printshape(obraz, size):
    i = 0
    for o in obraz:
        print "%s" % ( charfor(o) ),
        i+=1
        if i % size == 0: print

