##-----------------------SYED TABISH AZAM-----------------------------##

##-------------------Problem 2: Madam I’m Adam------------------------##
    
    ##PART (A)
def isPalindrome(x):
    if x.lower()[::-1] == x.lower():
        return 'TRUE'
    else:
        return 'FALSE'
    #PART (B)
def isPalindrome1(x):
    if len(x)==1:
        return True
    if x.lower()[0]== x.lower()[len(x)-1]:
        return True and isPalindrome1(x[1:len(x)-1])
    else:
        return False

##------------------------Problem 3: Base Conversion--------------------##

    ##PART (A)
def binaryString(x):
    if x < 0:
        return 'Must be a positive integer'
    p = 7
    representation = ""
    while p >=0:
        if x >= 2**p:
            representation = representation + "1"
            y = x - (2**p)
            x = y
            p -=1
        else:
            representation = representation + "0"
            p -=1
    return representation

    ##PART (B)
def binaryString1(x):
    if x < 0:
        return 'Must be a positive integer'
    elif x == 0:
        return '0'
    else:
        return binaryString1(x//2) + str(x%2)



##-----------------------------Problem 4: The Grid------------------------##
def grid(r,c,h,w):
    middle = ""
    plus = "+"
    minus = " - "
    flat = "|"
    space = "   "
    tempr=r
    while tempr>0:
        tempw = w
        temph = h
        tempc = c
        gap = ""
        above = plus + (((minus*tempw) + plus)*tempc) 
        middle = flat + (((space*tempw) + flat)*tempc)
        print(above)
        while temph > 0:
            print(middle)
            temph -= 1
        tempr-=1
    print(above)

##---------Problem 5: Transformations by Increment and Unfolding--------##
def transform(s,l):
    method = " "
    templ=l
    if s >= l:
        return "Please type the lower value first"
    while (templ  / 2) >= s:
        if templ%2 == 0:
            x = templ /2
            templ = x
            method = "* 2" + method
        else:
            x = templ - 1
            templ=x
            method = " + 1)" + method
    while templ >s:
        templ -=1
        method =  " + 1)" + method
    print(s,method)

##-----------------------Problem 6: Truth Combinations---------------##
    #PART (A):
def generateRow(n,count):
    power = 7
    representation = ""
    while power >=0:
        if count >= 2**power:
            representation = representation + "T"
            y = count - (2**power)
            count = y
            power -=1
        else:
            representation = representation + "F"
            power -=1
    print(representation[-n::])

    #PART (B):
def printTruthTable(n):
    row = 2**n
    count = 0
    while count < row:
        generateRow(n,count)
        count +=1

##----------------------Problem 7: Verdict Maths---------------------##
        #PART (A)
def exponentString(e):
    x= binaryString(e)
    one = x.find('1')
    rest = x[(one+1):]
    count = 0
    verdict = ""
    while count <= len(rest):
        if rest[count:count+1]=='1':
            verdict = verdict + " sx "
        elif rest[count:count+1]=='0':
            verdict = verdict + " s "
        count += 1
    return verdict

        #PART (B)

def computeExponent(x):
    lenght = len(x)
    exp = 1
    index= 0
    while index<=len(x):
        if x[index:index+1]=='s':
            exp = exp * 2
        elif x[index:index+1]=='x':
            exp = exp + 1
        index +=1
    print(exp)

##-------------------Problem 8: Yohsin Beads-------------------------##
    #PART (A)
def beads(n):
    x = binaryString(n)
    r = 1
    b = 1
    p = 1
    y = 1
    g = 1
    beads = ""
    one = x.find('1')
    if one==7:
        beads = "W"
        return beads
    rest = x[(one+1):]
    count = 0
    verdict = ""
    while count <= len(rest):
        if rest[count:count+1]=='1':
            verdict = verdict + "sx"
        elif rest[count:count+1]=='0':
            verdict = verdict + "s"
        z = verdict[count:count+1]
        if count == 0 and z == "s":
            beads = beads + "W" + "-W"
        elif count != 0 and z=="s":
            if r ==1:
                beads = beads + "-R"
                r -= 1
            elif b==1 and r!=1:
                beads = beads + "-B"
                b-=1
            elif p == 1 and b != 1:
                beads = beads + "-P"
                p-=1
            elif y == 1 and p != 1:
                beads = beads + "-Y"
                y-=1
            elif g == 1 and y != 1:
                beads = beads + "-G"
                g-=1
        elif count !=0 and z == "x":
            beads = beads + "-W"
        count += 1
    return beads    

    ##PART(B)
def maxBeads():
    beadscount = -1000
    x=1
    while x <=64:
        nob = beads(x)
        if len(nob)>beadscount:
            beadscount = len(nob)
            cell = x
        x += 1
    print("maximum beads required on cell number:",cell)

    ##PART (C)
def firstPurple():
    x = 1
    while x <=64:
        cob = beads(x)
        if cob.find('P') != -1:
            return x
        else:
            x +=1

    ##PART (D)
def rbpOnly():
    x = 64
    while x >=1:
        check = beads(x)
        if check.find("Y") > -1:
            return (x - 1)
        else:
            x -=1

##----------------------Problem 9: Elementary Recursion-------------------##
            ##PART (A)
def countHanoiMoves(x):
    return ((2**x)-1)

            ##PART (B)
def hanoi(n):
    hanoiMoves(n,1,3,2)
    return

def hanoiMoves(n,source,destination,helper):
    if n>=1:
        hanoiMoves(n-1,source,helper,destination)
        print("Move disk from bar",source,"to",destination)
        hanoiMoves(n-1,helper,destination,source)

##----------------------Problem 10: A Game Of throne------------------##
        ##PART (A)
def encrypt(x):
    count = 0
    final = ""
    while count <len(x):
        if x[count:count+1].isupper()== True:
            x = x.lower()
        if x[count:count+1] == " ":
            final = final + " "
        elif x[count:count+1] == "a":
            final = final + "k"
        elif x[count:count+1] == "b":
            final = final + "l"
        elif x[count:count+1] == "c":
            final = final + "m"
        elif x[count:count+1] == "d":
            final = final + "n"
        elif x[count:count+1] == "e":
            final = final + "o"
        elif x[count:count+1] == "f":
            final = final + "p"
        elif x[count:count+1] == "g":
            final = final + "q"
        elif x[count:count+1] == "h":
            final = final + "r"
        elif x[count:count+1] == "i":
            final = final + "s"
        elif x[count:count+1] == "j":
            final = final + "t"
        elif x[count:count+1] == "k":
            final = final + "u"
        elif x[count:count+1] == "l":
            final = final + "v"
        elif x[count:count+1] == "m":
            final = final + "w"
        elif x[count:count+1] == "n":
            final = final + "x"
        elif x[count:count+1] == "o":
            final = final + "y"
        elif x[count:count+1] == "p":
            final = final + "z"
        elif x[count:count+1] == "q":
            final = final + "a"
        elif x[count:count+1] == "r":
            final = final + "b"
        elif x[count:count+1] == "s":
            final = final + "c"
        elif x[count:count+1] == "t":
            final = final + "d"
        elif x[count:count+1] == "u":
            final = final + "e"
        elif x[count:count+1] == "v":
            final = final + "f"
        elif x[count:count+1] == "w":
            final = final + "g"
        elif x[count:count+1] == "x":
            final = final + "h"
        elif x[count:count+1] == "y":
            final = final + "i"
        elif x[count:count+1] == "z":
            final = final + "j"
        count +=1
    print(final)

    ##PART B
def decrypt(x):
    count = 0
    final = ""
    while count <len(x):
        if x[count:count+1].isupper()== True:
            x = x.lower()
        if x[count:count+1] == " ":
            final = final + " "
        elif x[count:count+1] == "a":
            final = final + "q"
        elif x[count:count+1] == "b":
            final = final + "r"
        elif x[count:count+1] == "c":
            final = final + "s"
        elif x[count:count+1] == "d":
            final = final + "t"
        elif x[count:count+1] == "e":
            final = final + "u"
        elif x[count:count+1] == "f":
            final = final + "v"
        elif x[count:count+1] == "g":
            final = final + "w"
        elif x[count:count+1] == "h":
            final = final + "x"
        elif x[count:count+1] == "i":
            final = final + "y"
        elif x[count:count+1] == "j":
            final = final + "z"
        elif x[count:count+1] == "k":
            final = final + "a"
        elif x[count:count+1] == "l":
            final = final + "b"
        elif x[count:count+1] == "m":
            final = final + "c"
        elif x[count:count+1] == "n":
            final = final + "d"
        elif x[count:count+1] == "o":
            final = final + "e"
        elif x[count:count+1] == "p":
            final = final + "f"
        elif x[count:count+1] == "q":
            final = final + "g"
        elif x[count:count+1] == "r":
            final = final + "h"
        elif x[count:count+1] == "s":
            final = final + "i"
        elif x[count:count+1] == "t":
            final = final + "j"
        elif x[count:count+1] == "u":
            final = final + "k"
        elif x[count:count+1] == "v":
            final = final + "l"
        elif x[count:count+1] == "w":
            final = final + "m"
        elif x[count:count+1] == "x":
            final = final + "n"
        elif x[count:count+1] == "y":
            final = final + "o"
        elif x[count:count+1] == "z":
            final = final + "p"
        count +=1
    print(final)

    ##PART (C)
def takeInput(string,choice):
    if choice.lower() == "encrypt":
        return encrypt1(string)
    elif choice.lower() == "decrypt":
        return decrypt1(string)
    else:
        return "ERROR ! Please Type 'Encrypt' or 'Decrypt'"

    ##PART (D)
def encrypt1(x):
    count = 0
    final = ""
    while count <len(x):
        if x[count:count+1] != " ":
            y= ord(x[count:count+1])
            if (y <= 112 and y >=97) or (y<=80 and y>=65): 
                decodedc = y + 10
            else:
                decodedc = y - 16
            final = final + chr(decodedc)
        else:
            final = final + " "
        count += 1
    print(final)

def decrypt1(x):
   count = 0
   final = ""
   while count <len(x):
       if x[count:count+1] != " ":
           y = ord(x[count:count+1])
           if (y <= 106 and y >=97) or (y<=74 and y>=65): 
               encoded = y + 16
           else:
               encoded = y - 10
           final = final + chr(encoded)
       else:
           final = final + " "
       count += 1
   print(final)


