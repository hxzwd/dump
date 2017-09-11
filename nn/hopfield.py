#!/usr/bin/python
# -*- coding: cp1251 -*-
#
# Author: Yaroslav Pogrebnyak (yyyaroslav@gmail.com)
# http://bitsofmind.wordpress.com
#

import sys
from hopfield.parser import parse, parse_shape, SHAPE_SIDE
from hopfield.net import HopfieldNet
from hopfield.util import printshape

knows_shapes_dir = "known_shapes"
modified_shape_path = "modified_shapes/modified.txt"


#
# ������� �������
#
def main(argv):

    shapes = parse(knows_shapes_dir)
    shape = parse_shape(modified_shape_path)

    print "Known Shapes:"
    for o in shapes:
        printshape(o, SHAPE_SIDE)
        print

    print "Teaching..."
    hopfield = HopfieldNet(SHAPE_SIDE)
    for o in shapes:
        hopfield.teach(o)
    print

    print "Modified shape:"
    printshape(shape, SHAPE_SIDE)
    print

    print "Shape recognizing..."
    (recognized, recshape, iters) = hopfield.recognize(shape)
    print

    if recognized:
        print "Success. Shape recognized in %g iterations:" % iters
    else:
        print "Fail. Shape not recognized in %g iterations..." % iters
    printshape(recshape, SHAPE_SIDE)

#
# ����� �����
#
if __name__ == '__main__':
    main(sys.argv[1:])

