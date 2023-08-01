#!/usr/bin/env python3
def getPointPositionsFromFile(name):
    f = open(name,"r")
    l=f.readline()
    N=int(l)
    X=[]
    Y=[]
    for i in range(N):
        l=f.readline()
        sp=l.split(" ")
        X.append(float(sp[0]))
        Y.append(float(sp[1]))
    return (X,Y)
