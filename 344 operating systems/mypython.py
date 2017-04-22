#!/usr/bin/python
#Jennifer Frase python assignment

import random
#open the files for writing only since we won't be reading
f1 = open("fe.txt", "w")
f2 = open("fi.txt", "w")
f3 = open("fo.txt", "w")

#save the files in an array for easy reference in the for loop
f = [f1,f2,f3]
letters = 'abcdefghijklmnopqrstuvwxyz'

#for each file pick 10 letters and save them to the that file
#before printing them
for i in range(0, 3):
   str = ""
   
   #pick 10 letters and append them onto str so that they appear
   #as one string with no white space
   for j in range(0, 10):
      str += random.choice(letters)

   #write the picked letters to the appropriate file and print
   #them to the screen
   f[i].write(str)
   print "File %s contains: %s" % (f[i].name,str)

#get two random numbers and print them and their product
num1 = random.randint(1,42)
num2 = random.randint(1,42)
print "The product of the random numbers %d and %d is %d" \
      % (num1,num2,num1*num2)

#close the files so they don't remain open
f1.close()
f2.close()
f3.close()

