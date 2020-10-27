import random

a=0.0
b=10.0


test1 = open("test1.txt","w")

for i in range(1000):
    test1.write(str(random.randint(a*10,b*10)/10) + " " +str(random.randint(a*10,b*10)/10)+ " " +str(random.randint(a*10,b*10)/10)  + " "+ str(random.randint(a*10,b*10)/10) + "\n")


testdiff = open("test1diff.txt","w")
for i in range(1000):
    testdiff.write(str(random.randint(a*10,b*10)/10) + " " +str(random.randint(a*10,b*10)/10)+ " " +str(random.randint(a*10,b*10)/10) + " "+ str(random.randint(a*10,b*10)/10) + "\n")


out = open("streamtext.txt","w")
for i in range(1000):
    out.write(str(random.randint(a*10,b*10)/10) + " " +str(random.randint(a*10,b*10)/10)+ " " +str(random.randint(a*10,b*10)/10) + " "+ str(random.randint(a*10,b*10)/10) + "\n")



file = open("streamtext.txt","r")

out = open("streaming1.txt","w")

counter = 1
for lines in file:

    counter1 = 0
    for num in lines.strip().split(" "):
        if counter1 == 0 :
            out.write("(" + str(counter) + ".0), [" + num )
        else :
            out.write(", " + num )

        counter1 +=1
    out.write("]\n")
    counter+=1
