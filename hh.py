heure=int(input("saisir l heure"))
minute=int(input("saisir les minutes"))
if heure==23 and minute==59:
    heure=0
    minute=0
elif minute==59:  
    minute=0
    heure+=1
else :
    minute+=1
print("la nouvelle heure est ",heure,minute)