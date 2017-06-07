import random
import math



#--------------------------Assignment 1b-------------------------------------#

def Anneal(func,maxMin):
    '''Returns maximum value of specified anneal ("himmelblau" or "rosenbrock")'''
    '''MaxMin specifies if we want to find the maximum of a function or minimum of a function'''
    #values calculated and applied to function to calculate respective fn
    if func == "rosenbrock":
        #Initial values of X and Y between -2 and 2
        xr = random.randint(-2,2)
        x = xr * random.random()
        #This random.random ensures floating points
        yr = random.randint(-1,3)
        y = yr * random.random()
        #Values saved as a tuple
        tup = (x,y)
        value = rosenbrock(tup)
    elif func == "himmelblau":
        #Initial values of X and Y between -4 and 4
        xr = random.randint(-6,6)
        x = xr * random.random()
        yr = random.randint(-6,6)
        y = yr * random.random()
        #Values saved as a tuple
        tup = (x,y)
        value = himmelblau(tup)
    else:
        print("No matching function found as: ",func)
        return
    #savetup and saveval, to save the highest found solution
    saveTup = tup
    saveValue = value
    #loop and reduce each time by factor of 0.99
    itering = 10000.0
    iteringMin = 1
    reducingFactor = 0.001
    while itering > iteringMin:
        tupNew = neighbor(tup,func)
        if func == "rosenbrock":
            neighborCost = rosenbrock(tupNew)
        elif func == "himmelblau":
            neighborCost = himmelblau(tupNew)
        probability = ap(value,neighborCost,itering,maxMin)
        #If probability is higher, then consider moving to neighbour
        var = random.random()
        if probability > var:
            tup = tupNew
            value = neighborCost
            if maxMin=="max":
                if value>saveValue:
                    print("Highest yet: ",value, " at ",tup)
                    saveValue = value
                    saveTup = tup
            if maxMin=="min":
                if value<saveValue:
                    print("Lowest yet: ",value, " at ",tup)
                    saveValue = value
                    saveTup = tup
        itering *= 1 - reducingFactor
    return saveTup,saveValue


#Returns the random neighbour from adjacent blocks#
def neighbor(tup,func):
    x = tup[0]
    y = tup[1]
    neigh = [(x,y+0.5),(x+0.5,y),(x-0.5,y),(x,y-0.5)]
    r =random.randint(0,3)
    i = neigh[r]
    #condition to ensure that x and y doesnt exceed the range
    while outOfRange(i,func):
        r =random.randint(0,3)
        i = neigh[r] 
    return i

#Checks if the found neighbours still lies in the range of fucntion
def outOfRange(tup,func):
    x = tup[0]
    y = tup[1]
    if func == "rosenbrock":
        if x>2 or x<-2:
            return True
        elif y>3 or y<-1:
            return True
    if func=="himmelblau":
        if x>6 or x <-6:
            return True
        if y>6 or y<-6:
            return True
    return False
        
#Acceptance Probability. Return 1 if neighbor is more suitable#
def ap(value,neighborCost,itering,maxMin):
    if maxMin == "max":
        if neighborCost > value :
            return 1
        a=   neighborCost - value
    if maxMin =="min":
        if neighborCost < value :
            return 1
        a=   value - neighborCost 
    
    b = a/itering
    
    c = math.exp(b)
    return c
    
##-----------------Function Equations------------------##
def rosenbrock(tup):
    a = pow((1-tup[0]),2)
    x2 = pow(tup[0],2)
    b = pow(tup[1]-x2,2)
    c = a + (100*b)
    return c

def himmelblau(tup):
    x = tup[0]
    y = tup[1]
    x2 = pow(x,2)
    y2 = pow(y,2)
    brack1 = x2 + y -11
    brack2 = x + y2 - 7
    f1 = pow(brack1,2)
    f2 = pow(brack2,2)
    fn = f1+f2
    return fn
