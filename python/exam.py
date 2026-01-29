def addi(l1,l2):
    N=[]
    if len(l1)>len(l2):
        n=min(len(l1),len(l2))
        for i in range(0,n):
            N.append(l1[i]+l2[i])
        for i in range(n,len(l1)):
            N.append(l1[i])
    if len(l1)<len(l2):
        n=len(l2)-len(l1)
        for i in range(0,n):
            N.append(l1[i]+l2[i])
        for i in range(n,len(l2)):
            N.append(l2[i])
    for i in range(0,len(l1)):
            N.append(l1[i]+l2[i])
    return N