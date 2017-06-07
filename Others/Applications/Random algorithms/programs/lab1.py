def binarystring(x):
    br = 1
    power = 7
    while power >=0:   
        if x >= 2**(power):
            br = br + "1"
            y = x - (2**(power))
            x = y
            power -= 1
        elif x < 2**(power):
            br = br + "0"
            power -= 1
    return br

def binarystring1(x):
    if x == 0:
        return '0'
    else:
        return binarystring1(x//2) + str(x%2)

def grid(r,c,w,h):
    top = "+"
    left = "|"
    line = " - - +"
    line2= "|"
    while c >0:
        top = top + line
        c -= 1
    print(top)
    while h>0:
        h -= 1
        print(line2, line, "\n" )
