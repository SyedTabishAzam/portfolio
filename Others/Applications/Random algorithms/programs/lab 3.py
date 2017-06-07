### Tabish Sakina Fatin and Hamza ###
import ParseTree

def isoperator(s):
    if s=="+" or s=="-" or s=="*" or s=="/" or s=="**" or s == "//" or s == "%":
        return True
    else:
        return False
    
def precedence(op):
    if op == "**":
        return 6
    if op == "*":
        return 5
    if op == "/":
        return 4
    if op == "//":
        return 3
    if op == "%":
        return 2
    if op == "+":
        return 1
    if op == "-":
        return 0
    return False
    
def getNumberIndex(s):
    ##returns the first index in s
    ##that is not part of a number.
    ##If there is no number at the beginning of s,
    ##the function returns 0.
    s=s.strip()
    s = s.replace(" ","")
    if (s[0]!= "-" and s[0]!="+") and s[0].isnumeric()==False and s[0]!=".":
        return 0
    count = 1
    while  count<len(s) and (s[count].isnumeric()==True or s[count]=="."):
        count +=1
    return count
            

def getOperatorIndex(s):
    ##returns the first index in s
    ##that is not part of an operator.
    ##If there is no operator at the beginning of s,
    ##the function returns 0.
    s=s.strip()
    s = s.replace(" ","")
    if s[0]!= "-" and s[0]!= "+" and s[0]!= "*" and s[0]!= "/":
        return 0
    count = 1
    while count < (len(s)-1):
        if isoperator(s[count])==False:
            return count
        elif (s[count]=="-" or s[count]=="+") and isoperator(s[count-1])== True:
            return count
        else:
            count +=1
    return count

def tokenizeSimple(s):
    s=s.strip()
    tokens = []
    idx = getNumberIndex(s)
    tokens.append(s[:idx])
    s = s[idx:]
    while s!= "" :
        s = s.strip()
        idx = getOperatorIndex(s)
        tokens.append(s[:idx])
        s = s[idx:]
        s = s.strip()
        idx = getNumberIndex(s)
        tokens.append(s[:idx])
        s = s[idx:]
    return tokens
    


    
from ParseTree import Node
def makeparsetreePM(t):
    
    count = 0
    operator = 0
    root = Node('')
    n = Node('')
    while count < len(t):
        
        if isoperator(t[count]) == True and root.getData()== '':
            root.setData(t[count])
        if isoperator(t[count]) == True and root.getLeft()==None:
            root.setLeft(Node(t[count-1]))
        if isoperator(t[count]) == True and root.getRight()== None:
            root.setRight(Node(t[count+1]))
        if (count+2)<len(t) and t[count].isnumeric()==False:
            n=Node((t[count+2]))
            n.setLeft(root)
            root = root.getParent()
        count = count + 1
    return root

def makeparsetreeMD(t):
    
    count = 0
    operator = 0
    root = Node('')
    n = Node('')
    while count < len(t):
        
        if isoperator(t[count]) == True and root.getData()== '':
            root.setData(t[count])
        if isoperator(t[count]) == True and root.getLeft()==None:
            root.setLeft(Node(t[count-1]))
        if isoperator(t[count]) == True and root.getRight()== None:
            root.setRight(Node(t[count+1]))
        if (count+2)<len(t) and t[count].isnumeric()==False:
            n=Node((t[count+2]))
            n.setLeft(root)
            root = root.getParent()
        count = count + 1
    return root

def prefix(root):
    x= []
    steps = 0
    if root.getParent()==None:
       y= str(root.getData())
       x.append(str(root.getData()))
    while root.getLeft()!= None:
        z = str(root.getLeft())
        x.append(str(root.getLeft().getData()))
        root = root.getLeft()
        steps = steps + 1
    while steps >0:
        root = root.getParent()
        x.append(str(root.getRight().getData()))
        steps = steps - 1
    return x

def evaluatePM(t):
    index = len(t)
    nstack=[]
    opstack=[]
    while index >0:
        currentc = t[index-1]
        if currentc.isnumeric()==True or (len(currentc)>=2 and (currentc[0]=="-" or currentc[0]=="." or currentc[0]=="+")):
            nstack.append(currentc)
        elif isoperator(currentc)== True:
            aov = nstack.pop()
            bov = nstack.pop()
            if currentc=="+":
                nstack.insert(len(nstack),float(aov) + float(bov))
            elif currentc=="-":
                nstack.insert(len(nstack),float(aov) - float(bov))
        index = index - 1
    return nstack

def evaluateMD(t):
    index = len(t)
    nstack=[]
    opstack=[]
    while index >0:
        currentc = t[index-1]
        if currentc.isnumeric()==True or (len(currentc)>=2 and (currentc[0]=="-" or currentc[0]=="." or currentc[0]=="+")):
            nstack.append(currentc)
        elif isoperator(currentc)== True:
            aov = nstack.pop()
            bov = nstack.pop()
            if currentc=="*":
                nstack.insert(len(nstack),float(aov) * float(bov))
            elif currentc=="/":
                nstack.insert(len(nstack),float(aov) / float(bov))
            elif currentc=="**":
                nstack.insert(len(nstack),float(aov) ** float(bov))
            elif currentc=="//":
                nstack.insert(len(nstack),float(aov) // float(bov))
            elif currentc=="%":
                nstack.insert(len(nstack),float(aov) % float(bov))
        index = index - 1
    return nstack

######################## ----- Bonus tokenize ----- #######################
def tokenize(s):
    dummy = s
    s=s.strip()
    dummy=dummy.strip()
    tokens = []
    while s.find("(")!=-1:
        bo = s.find("(")
        bc = s.find(")")
        start = s[:bo]
        mid = s[bo+1:bc]
        end= s[bc+1:]
        s = start +mid + end
    idx = getNumberIndex(s)
    tokens.append(s[:idx])
    s = s[idx:]
    while s!= "" :
        s = s.strip()
        idx = getOperatorIndex(s)
        tokens.append(s[:idx])
        s = s[idx:]
        s = s.strip()
        idx = getNumberIndex(s)
        tokens.append(s[:idx])
        s = s[idx:]
    wfbo = dummy.replace(")","")
    while wfbo.find("(")!=-1:
        bo = wfbo.find("(")
        tokens.insert(bo,"(")
        wfbo = wfbo.replace("("," ",1)
    while dummy.find(")")!=-1:
        bc = dummy.find(")")
        tokens.insert(bc,")")
        dummy = dummy.replace(")"," ",1)
        
    return tokens

#############################------Function for my understanding--------------###########################
def makeprefix(t):
    index = len(t)
    prestack=[]
    stack=[]
    while index >0:
        currentc = t[index-1]
        if currentc.isnumeric()==True:
            prestack.append(currentc)
        elif isoperator(currentc)== True:
            stack.append(currentc)
        elif currentc== ")":
            stack.append(currentc)
        elif currentc=="(":
            count = (len(stack) - 1 )
            while stack[count] != ")" :
                print ("st1",stack)
                prestack.append(stack.pop())
                count -=1
            stack.pop()
        elif isoperator(currentc)==True:
            if precedence(currentc) >= precedence(stack[len(stack)-1]):
                stack.append(currentc)
            else:
                while precedence(currentc) < precedence(stack[len(stack)-1]):
                    print ("st2",stack)
                    prestack.append(stack.pop())
                prestack.append(stack.pop())
        index -= 1
    prestack.reverse()
    j = stack + prestack
    return j
