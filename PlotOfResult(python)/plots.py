import numpy as np
import matplotlib.pyplot as plt
import math
from readfile import getPointPositionsFromFile as gppff
import sys
showC= int(sys.argv[2])
fileName = sys.argv[1]

simpl=[[] for x in range(2)]
simplX=[[] for x in range(2)]
simplY=[[] for x in range(2)]
maxpdb=0
with open("../ComputationOfHomology(cpp)/output/Persistant_Diagram_Data.txt") as openfileobject:
    for line in openfileobject:
        k=line.split("|")
        limits = k[-1].split(" ") 
        if float(limits[1])<float(limits[0]) and float(limits[1])!=-1:
            continue
        elif(float(limits[1])>maxpdb):
            maxpdb=float(limits[1])
        tmp=[]
        i=0
        while(i<len(k)-1):
            tmp2=[]
            for s in k[i].split(" "):
                tmp2.append(int(s))
            tmp.append(tmp2)
            i+=1
        dim=len(tmp[0])
        if dim>2:
            continue
        simpl[dim-1].append(tmp);
        limits = k[i].split(" ")
        simplX[dim-1].append(float(limits[0]))
        if(float(limits[1])!=-1):
            simplY[dim-1].append(float(limits[1]))
        else:
            simplY[dim-1].append(float(maxpdb))
    l=[]
    maxpdb+=50
    for i,j in zip(simplX,simplY):
        l.append(plt.scatter(i,j))
    plt.plot([x for x in range(0,2000)])
    plt.axis([-0.25, maxpdb, 0, maxpdb])
    plt.legend((l[0], l[1]),
           ('0-simplex', '1-simplex'),
           scatterpoints=1,
           loc='upper left',
           ncol=1,
           fontsize=8)
    plt.xlabel("Distance at which simplex was created")
    plt.ylabel("Distance at which simplex disappears")
    plt.savefig('../output/PD')
    if(showC==1):
        plt.show()
    else:
        plt.clf()
for i in range(len(simpl[1])):
    tmp=[]
    for j in simpl[1][i]:
        if simpl[1][i].count(j)%2!=0 and  j not in tmp:
            tmp.append(j)
    simpl[1][i]=tmp



(allx,ally)=gppff(fileName)

count =0

for i in range(len(simpl[1])):
    plt.scatter(allx, ally, c='C0')
    for j in simpl[1][i]:
        plt.plot([allx[j[0]],allx[j[1]]],[ally[j[0]],ally[j[1]]], linestyle="-")
    #print(simpl[1][i],simplX[1][i],simplY[1][i])
    count+=1
    plt.savefig('../output/c'+str(i))
    if(showC==1):
        plt.show()
    else:
        plt.clf()
print(count)
