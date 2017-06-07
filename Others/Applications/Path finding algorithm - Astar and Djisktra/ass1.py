import matplotlib.pyplot as plt
import networkx as nx
import graphviz
import csv
import operator
import random


##-------------------------------------------Assignment 1a-------------------------------------#
#Globally create connections list to be used by individual functions#
connections = []
csvfile = open("connections.csv")
formatedFile = csv.reader(csvfile,delimiter=',',quotechar="|")
for row in formatedFile:
    connections.append(row)




    
#A star algorithm, gets the start and end city as arguments#        
def astar(start,end):
    #Initialize graph
    h = nx.DiGraph()
    
    destination = end
    hArr = []

    #Open heuristics file, and gets the appropriate heuristic information according to the destination city#
    csvfile = open("heuristics.csv")
    formatedFile = csv.reader(csvfile,delimiter=',',quotechar="|")
    firstRow = next(formatedFile)
    hOf = firstRow.index(end)
    for row in formatedFile:
        hArr.append(tuple((row[0],row[hOf])))

    #openArr is a dict, to maintain the parent and child information#
    openArr = {}
    

    #Start node added to openArr with heuristic , and level = 0
    openArr[(start,heuristics(hArr,start))]=0
    
    
    #openList contains the city with its fn
    
    
    #Close array, allso a dict
    close = {}
    
    
    #Soution array initialized
    sol = []
    
            
    #Loop till openArr is not Empty
    while len(openArr) >0:
        
        lowest = 9999999
        #finding node with least fn
        for node in openArr:
            if int(node[1])<lowest:
                lowest=int(node[1])
                currentNode = node
        level = openArr.get(currentNode)
        #Level contains the level of the node that is being examined#
        

        
        openArr.pop(currentNode)
        
        #Remove the currentNode from openArray and NotVisited ( because its going to be visited now)
        
        
              
        #If we have the the destination in currentNode, end#
        if currentNode[0] == destination:
            #Add currentNode in Closed#
            close[currentNode]=level
            
            sol = []
            sol.append(currentNode[0])
            
            parent = currentNode
            
           #This whole thing connects the destination node to its parent , unless start Node is met. 
            while parent[0] != start:
                #Dictinoery Compression used here.
                print(close.items())
                check = {k:v for k,v in close.items() if v==level-1}
                print(check)
                for i in check:
                    if isConnected(i,parent) != -1:
                        
                        savParent = i
                        level = close[savParent]
                        #Solution appended to sol array
                        sol.append(i[0])
                parent = savParent
       
            sol.reverse()
            print("Solution Found",sol)
            #adds the path to the graph, and returns the graph
            h.add_path(sol)
            return h
            
        
        #Finds the index of currentNode in the row#
        row = connections[0].index(currentNode[0])
        
        #For each child of currentNode
        for col in range(1,len(connections[row])):
            if int(connections[row][col])>0:
                #cost is the connection value and the travelCost till current Node
                cost =  uptil(currentNode,hArr) + int(connections[row][col]) 
                
                #name of city being observed
                city = connections[0][col]
                
                existOpen= False
                existClosed = False

                #These two loop checks if the file exists in openArr and closeArray
                for i in openArr:
                    if i[0]==city:
                        q=i
                        existOpen = True
                        break
                    
                for i in close:
                    if i[0]==city:
                        v=i
                        existClosed = True
                        break
                #If it exsist in open, and if the travelcost is already lesser than current cost, do nothing just continue to next child
                if existOpen:
                    if uptil(q,hArr)<=cost:
                        continue

                #if it exist in closed, if the travel cost is lesser than current cost, do nothing just continue to next child
                elif existClosed:
                    if uptil(v,hArr)<=cost:
                       
                        continue
                    #else if the travel cost of found is higher than current cost, remove it from closed and add to open
                    
                    close.pop(v)
                    
                    openArr[v]=level
                    
                    
                else:
                    #if no condition is met, calculate heuristic (hArr contains heuristic data)
                    hn= heuristics(hArr,city)
                
                tup = (city,hn+cost)

                #Add the child to open Array
                openArr[tup]=level+1
                
                
        close[currentNode]=level
        

    #If all the nodes are vistied, destination isnt found
    if currentNode[0] != destination:
        print("Not Found")
                   

#Function that calculates heuristics from the hArr
def heuristics(remain,city):
    val = dict(remain)[city]
    return int(val)

#Function that calculates the travel Cost (g(n))#
def uptil(tup,remain):
    gn =   int(tup[1]) - heuristics(remain,tup[0])
    return gn

#function that checks if the two cities are connected, i.e they dont have a -1#
def isConnected(n1,n2):
    n1Name = n1[0]
    n2Name = n2[0]
    r = connections[0].index(n1Name)
    c = connections[0].index(n2Name)
    return int(connections[r][c])

      
def makeGraph(g):
    l = 0
    pos = {}
    nodes = sorted(g.nodes(), key=lambda x: x[1])
    edges = g.edges()
    edge_label = {}
    for i in edges:
        edge_label={i:isConnected(i[0],i[1])
                    }
   
    return g.copy()
    
#Map of each and every node is made from Cities file and returned as graph#   
def makeMap():
    allCities = []
    csvfile = open("cities.csv")
    formatedFile = csv.reader(csvfile,delimiter=',',quotechar="|")
    for row in formatedFile:
        allCities.append(row)
        
    h = nx.Graph()
    for i in allCities:
        for j in allCities:
            if isConnected(i,j)>0:
                h.add_edge(i[0],j[0])
    

   
    return h.copy()


#Bfirst, similar to A*, just use heuristic to calculate the distance
def bfirst(start,end):
    h = nx.DiGraph()
    
    destination = end
    hArr = []
    
    csvfile = open("heuristics.csv")
    formatedFile = csv.reader(csvfile,delimiter=',',quotechar="|")
    firstRow = next(formatedFile)
    hOf = firstRow.index(end)
    for row in formatedFile:
        hArr.append(tuple((row[0],row[hOf])))
   
    openArr = {}
    notVisited = []
    
    openArr[(start,heuristics(hArr,start))]=0
    notVisited.append((start,heuristics(hArr,start)))
    
    #openList contains the city with its fn
    
    
    
    close = {}
    
    
    sol = []
    visited = []
    
    #Loop till openArr is not Empty
    while len(openArr) >0:
        
        lowest = 9999999
        #finding node with least fn
        for node in openArr:
            if int(node[1])<lowest:
                lowest=int(node[1])
                currentNode = node
        level = openArr.get(currentNode)
        
        

        
        openArr.pop(currentNode)
        
        #openArr = {k:v for k,v in openArr.items() if v<level}
        
        notVisited.remove(currentNode)       

        if currentNode[0] == destination:
            close[currentNode]=level
            
            sol = []
            sol.append(currentNode[0])
            
            parent = currentNode
           
            while parent[0] != start:
                check = {k:v for k,v in close.items() if v==level-1}
                for i in check:
                    
                    if isConnected(i,parent) != -1:
                        parent = i
                        level = close[parent]
                        sol.append(i[0])
       
            
            print("Solution Found",sol)
            h.add_path(sol)
            return h
            
        

        row = connections[0].index(currentNode[0])
        
        #For each child of currentNode
        
        
        for col in range(1,len(connections[row])):
            if int(connections[row][col])>0:
                #cost is that value + value till parrentNode 
                city = connections[0][col]
                cost = heuristics(hArr,city)
                
                existOpen= False
                existClosed = False
                for i in notVisited:
                    if i[0]==city:
                        q=i
                        existOpen = True
                        break
                    
                for i in visited:
                    if i[0]==city:
                        v=i
                        existClosed = True
                        break
                    
                if existOpen:
                    if uptil(q,hArr)<=cost:
                        
                        continue
                elif existClosed:
                    if uptil(v,hArr)<=cost:
                       
                        continue
                    visited.remove(v)
                    close.pop(v)
                    
                    openArr[v]=level
                    notVisited.append(v)
                    
                else:
                    
                    hn= heuristics(hArr,city)
                
                tup = (city,hn)
                
                openArr[tup]=level+1
                notVisited.append(tup)
                
        close[currentNode]=level
        visited.append(currentNode)

        
    if currentNode[0] != destination:
        print("Not Found")


#Function that calculates using djikstra algorithm#
def djikstra(start,end):
    g = nx.Graph()
    allCities = []
    csvfile = open("cities.csv")
    formatedFile = csv.reader(csvfile,delimiter=',',quotechar="|")
    for row in formatedFile:
        allCities.append(row)
        
    visited = []
    
    unvisited = {}
    
    level = 0

    #Create each and every node in allCities and assign a starting value
    for nodes in allCities:
        if nodes[0] == start:
            unvisited[(nodes[0],level)]=0
        else:
            unvisited[(nodes[0],len(allCities))]=999999
    
    #Current Node is the start node#
    current = start
    

    
    while True:
        row = connections[0].index(current)

        #Explore all unvisited neighbour of current Node
        for x in unvisited:
            contin = False
            col = connections[0].index(x[0])
            if int(connections[row][col])>0:
                city = connections[0][col]
                y = [(u,v) for u,v in unvisited if u==current]
                cost = unvisited[y[0]]+int(connections[row][col])
                #update the cost from infinity to the connection cost
                g.add_edge(current[0],city)
                
                x = [(u,v) for u,v in unvisited if u==city]
                
                unvisited.pop(x[0])
                unvisited[(city,level+1)]=cost
                contin = True

        #Once the node is visited, add to visited arr
        y = [(u,v) for u,v in unvisited if u==current]
        level = y[0][1]+1
        visited.append((current,level))
        
        unvisited.pop(y[0])
        
        #if the visited list contains the end node, solution is found
        for nodes in visited:
            if nodes[0]==end:
                print(visited)
                print("Found, all the explored nodes are in Red")
                return g
        
        
        #Choose the node with lowest value from unvisited to explore next
        lowest = 9999999
        for j in unvisited:
            if unvisited[j]<lowest:
                lowest = unvisited[j]
                current = j[0]
                
    print ("Nothing Found")


#Route takes a start and end location, and a search type to search for the solution
def route(start,end,search):
    '''Start is starting city, end is destination city, search is the type ("astar" or "djikstra" or "bfirst")'''
    #Norht Graph contains a map of each and every city 
    northGraph = makeMap()

    #Rmap contains a searched map according to the algorithm
    if search=="astar":
        rmap = astar(start,end)
    elif search =="bfirst":
        rmap = bfirst(start,end)
    elif search=="djikstra":
        rmap = djikstra(start,end)

    #Connected contains all the edges that are connected in the Big Map
    connected = northGraph.edges()
    rEdges=rmap.edges()
    edge_color = {}
    edge_labels = {}
    copy = nx.Graph()

    #If the edges connected, also are the edges that is the solution, color accordingly
    for x in connected:
        edge_labels[x] = isConnected([x[0]],[x[1]])
        if x in rEdges or (x[1],x[0]) in rEdges:
            copy.add_edge(x[0],x[1],color='r',weight=2)
        else:
            copy.add_edge(x[0],x[1],color='b',weight=1)
    
    
    
    edges=copy.edges()
    colors = [copy[u][v]['color'] for u,v in edges]
    weights = [copy[u][v]['weight'] for u,v in edges]

    #Position set for list
    li = ["Islamabad","Taxila","Murree","Nathiagali","Abbottabad","Mansehra",
          "Balakot","Kaghan","Naran","Chilas","Bisham","Gilgit","Hunza",
          "Khunjerab Pass","Malam Jabba","Skardu","Muzaffarabad"]
    
    pos = {li[0]:(5,-1),
           li[1]:(1,0),
           li[2]:(9,1),
           li[3]:(8,3),
           li[4]:(5,4),
           li[5]:(4,6),
           li[6]:(7,8),
           li[7]:(9,9),
           li[8]:(10,12),
           li[9]:(12,14),
           li[10]:(3,11),
           li[11]:(15,15),
           li[12]:(16,19),
           li[13]:(19,20),
           li[14]:(0,9),
           li[15]:(16,10),
           li[16]:(10,6)}

    #Graph and labels drawn#
    nx.draw(copy,with_labels=True,pos=pos,edge_color=colors,width=weights)
    nx.draw_networkx_edge_labels(copy,pos=pos,edge_labels=edge_labels,with_labels=True)
  
    
    #Graph and labels shown and saved#
    plt.savefig("graph.png")
    plt.show()
