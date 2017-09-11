#!/usr/bin/python
# -*- coding: cp1251 -*-
#
# Author: Yaroslav Pogrebnyak (yyyaroslav@gmail.com)
# http://bitsofmind.wordpress.com
#

import random
import math

#
# Нейронная сеть Хопфилда
#
class HopfieldNet:

    #
    # Инициализация сети
    #
    def __init__(self, shapeside):
        self.drawsteps = False
        self.W = []      # матрица весовых коефицентов
        self.shapes = []  # образы, которым обучена сеть
        self.neurons = int(math.pow(shapeside,2))  # количество нейронов
        self.shapeside = shapeside # количество бит в стороне образа
        r = range(0, self.neurons)
        for i in r:
            self.W.append([0 for x in r])
        self.maxjunkiters = 200 # максимальное число безрезультатных итераций
        self.junkiter = 0 # текущая безрезультатная итерация

    #
    # Обучение сети образу
    #    
    def teach(self, shape):
        self.shapes.append(shape) 
        self.X = shape
        r = range(0, self.neurons)
        for i in r:
            for j in r:
                if (i == j):
                    self.W[i][j] = 0
                else:
                    self.W[i][j] += self.X[i] * self.X[j]

    # 
    # Распознать изменённый образ
    #
    def recognize(self, shape):
        self.Y = shape
        iter = 0
        # пока не совпадёт с одним из известных...
        while(self.shapes.count(self.Y) == 0):
            self.recstep()
            iter += 1
            # ... или количество безрезультатных итераций не истечёт
            if self.junkiter >= self.maxjunkiters:
                return (False, self.Y, iter)
        return (True, self.Y, iter)

    #
    # Шаг распознования.
    # Случайно выбирается нейрон для обновления 
    #
    def recstep(self):
        signum = lambda x : cmp(x,0)

        r = random.randrange(0, self.neurons, 1)
        net = 0
        for i in range(0, self.neurons):
            net += self.Y[i] * self.W[i][r]
        signet = signum(net)
        if signet != self.Y[r]: # заменяем текущий нейрон
            print "Neuron %3g : %2g  ->  %2g" % (r,self.Y[r],signet)
            self.Y[r] = signet
            if self.drawsteps:
                printshape(self.Y, self.shapeside)
                print
            self.junkiter = 0
        else:
            self.junkiter += 1 


