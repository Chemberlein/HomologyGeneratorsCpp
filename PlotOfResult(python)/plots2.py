import numpy as np
import matplotlib.pyplot as plt
import math
from readfile import getPointPositionsFromFile as gppff
import sys
showC= int(sys.argv[2])
fileName = sys.argv[1]

simpl=[]

with open("../ComputationOfHomology(cpp)/output/H1_homology_generators.txt") as openfileobject:
    for line in openfileobject:
        k=line.split("|")
        tmp=[]
        i=0
        while(i<len(k)-1):
            tmp2=[]
            for s in k[i].split(" "):
                tmp2.append(int(s))
            tmp.append(tmp2)
            i+=1
        simpl.append(tmp);
(allx,ally)=gppff(fileName)

for i in range(len(simpl)):
    for j in simpl[i]:
        plt.plot([allx[j[0]],allx[j[1]]],[ally[j[0]],ally[j[1]]], linestyle="-")
    plt.savefig('../output/homologyGenerators'+str(i))
    plt.scatter(allx, ally, c='C0')
    for i in range(len(allx)):
        label = str(i)
        plt.annotate(label,(allx[i],ally[i]),
                 textcoords="offset points",
                 xytext=(0,5),
                 ha='center')
    if(showC==1):
        plt.show()
    else:
        plt.clf();
