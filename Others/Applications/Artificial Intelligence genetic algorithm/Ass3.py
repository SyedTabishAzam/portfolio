
"""
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""
import re
import matplotlib.pyplot as plt
import math
import numpy as np
import random
pool = []
#  We use a regex here to clean characters and keep only numerics

cities_set = []
cities_tups = []
cities_dict = {}
#  we open the TSP file and put each line cleaned of spaces
#  and newline characters in a list 
def read_tsp_data(tsp_name):
	tsp_name = tsp_name
	with open(tsp_name) as f:
		content = f.read().splitlines()
		cleaned = [x.lstrip() for x in content if x != ""]
		return cleaned
"""
We return a list like 
['NAME: ulysses16.tsp',
'TYPE: TSP',
'COMMENT: Odyssey of Ulysses (Groetschel/Padberg)',
'DIMENSION: 16',
'EDGE_WEIGHT_TYPE: GEO',
'DISPLAY_DATA_TYPE: COORD_DISPLAY',
'NODE_COORD_SECTION',
'1 38.24 20.42',
'2 39.57 26.15',
'3 40.56 25.32',
................
'EOF']
"""

"""
Check for the line DIMENSION in the file and keeps the numeric value
"""
def detect_dimension(in_list):
	non_numeric = re.compile(r'[^\d]+')
	for element in in_list:
		if element.startswith("DIMENSION"):
			return non_numeric.sub("",element)

"""
Iterate through the list of line from the file
if the line starts with a numeric value within the 
range of the dimension , we keep the rest which are
the coordinates of each city
1 33.00 44.00 results to 33.00 44.00
"""
def get_cities(list,dimension):
	dimension = int(dimension)
	for item in list:
		for num in range(1, dimension + 1):
			if item.startswith(str(num)):
				index, space, rest = item.partition(' ')
				if rest not in cities_set:
					cities_set.append(rest)
	return cities_set


"""
Brake each coordinate 33.00 44.00 to a tuple ('33.00','44.00')
"""
def city_tup(list):
	for item in list:
		first_coord, space, second_coord = item.partition(' ')
		cities_tups.append((first_coord.strip(), second_coord.strip()))
	return cities_tups

"""
We zip for reference each city to a number
in order to work and solve the TSP we need a list 
of cities like 
[1,2,3,4,5,...........]
with the dictionary we will have a reference of the coordinates of each city 
to calculate the distance within (i + 1, i) or (2 - 1) were 2 and 1 represents each city
"""
def create_cities_dict(cities_tups):
	return zip((range(1,len(cities_tups))),cities_tups)

"""
Just to plot the results
"""
def plot_cities(cities_tups):
        
        plt.clf()
        plt.scatter(*zip(*cities_tups))
        plt.plot(*zip(*cities_tups))
        plt.show()


"""
Putting it all together
"""
def produce_final(file="qa194.tsp"):
	data = read_tsp_data(file)
	dimension = detect_dimension(data)
	cities_set = get_cities(data,dimension)
	cities_tups = city_tup(cities_set)
	cities_dict = create_cities_dict(cities_tups)
	#plot_cities(cities_tups)
	return (cities_dict)
	
def fitness(li):
        '''Calculates the fitness based on length of travel (total length)'''
        total = 0
        for x in range(1,len(li)):
                
                total = total + eDistance(li[x-1][1],li[x][1])
        return total

def parsePopulation(pp):
        '''Reformats the data in the form (x,y) where x is the route and y is the total cost of route'''
        candidates = []
        for x in pp:
                candidates.append((x,fitness(x)))
        return candidates

def FitnessTournament(candidates):
        '''selects candidates based on their fitness. The selected candidates number are ensured to be in power of 2'''
        candidates = sorted(candidates, key=lambda x: x[1])[0:next_lowest_pow2(len(candidates))]
        return candidates

def binaryTournament(candidates):
        
        winners = []

        runUntil = next_lowest_pow2(len(candidates))
        while len(winners) != runUntil:
                player1 = random.randint(0,len(candidates)-1)
                player2 = random.randint(0,len(candidates)-1)
                while player2==player1:
                        player2 = random.randint(0,len(candidates)-1)
                if candidates[player1][1]<candidates[player2][1] and (candidates[player1] in winners)==False:           
                        winners.append(candidates[player1])
                        candidates.remove(candidates[player1])
                elif candidates[player1][1]>candidates[player2][1] and (candidates[player2] in winners)==False:
                       
                        winners.append(candidates[player2])
                        candidates.remove(candidates[player2])
                
        
        return winners

def next_lowest_pow2(x):
        '''calculates the maximum power of 2 lesser than x'''
        x = x - 1
        x = x | x>>1
        x = x | x>>2
        x = x | x>>4
        x = x | x>>8
        x = x | x>>16
        x = x + 1
        x = x >> 1
        return x
        
def eDistance(p1,p2):
        '''calculates euclidean distance between two points'''
        x1 = float(p1[0])
        x2 = float(p2[0])
        y1 = float(p1[1])
        y2 = float(p2[1])
        return math.sqrt((pow((x1-x2),2))+(pow((y1-y2),2)))

def init_population(size):
        '''initializes popoulation randomly from the tsp file'''
        totalPop = list(produce_final())
        p = []
        li = [x for x in range(1,193)]
        random.shuffle(li)
        exploredList = []
        #Loop depends on population size. and li is generated that is the shuffled list from all to all the elements
        while size>0:
                minimum = 999999
                element = 0
                
                x = random.randint(0,190)
                if (x in exploredList)==False:
                        exploredList.append(x)
                        mapList = [] 
                        mapList.append(x)
                        
                        for loop in range(0,193):
                                for y in li:
                                        distance = eDistance(totalPop[x][1],totalPop[y][1])
                                        
                                        if y!=x and (distance<minimum) and (y in mapList)==False:
                                                mimimum = distance
                                                element = y
                                                
                                mapList.append(element)
                                x = y
                        
                        mapToPop = [totalPop[x] for x in mapList]
                        
                        p.append(mapToPop)
                        size = size - 1
       
        return p


def EA(populationNumber,offspringNumber,generationNumber):
        '''PROCESS EVERYTHING'''

        #Creates empty pool
        pool = []
        #And initialize population randomly in beginning (of size specified)
        pop = init_population(populationNumber)
        candidates = parsePopulation(pop)
        pool = candidates

        #X axis and Y axis are made to plot Graph
        xAxis = []
        yAxis = []
        avgX = []
        #Loops until generation number
        for loop1 in range(0,generationNumber):
                print(generationNumber/(generationNumber-loop1),"percent")
                #Parents are selected from pool on each generation, based on fitneess
                selectedParents = FitnessTournament(pool)


                #Each loop produce 2 offspring, so loop running accordingly
                for loop2 in range(0,int(offspringNumber/2)):
                        print((offspringNumber/2) / ((offspringNumber/2)-loop2),"percent")
                        #If no parents to choose from, break the loop
                        if(len(selectedParents)<2):
                                break

                        #Choose random 2 parents from the set of pool
                        choose2= random.sample(selectedParents,2)

                        #Remove the chosen parents from the parents pool
                        selectedParents = [x for x in selectedParents if (x in choose2)==False]

                        #Produce offspring using Crossover
                        offSpring = Crossover(choose2)

                        #Mutate if probabilty is 0.7
                        if random.random()<0.7:
                                offSpring = mutation(offSpring)

                        #Add the mutated/non-mutated offspring to the pool in a particular format
                        pool = pool + parsePopulation(offSpring)

                #Append X axis and Y axis for graph
                yAxis.append(loop1)
                xAxis.append(min(pool, key=lambda x:x[1])[1])

                #Append Average X on each iteration
                avgX.append(sum([x[1] for x in pool]) / len(pool))

        #Plot a graph
        
        plot(xAxis,avgX,yAxis)
        xx = min(pool, key=lambda x:x[1])
        xa = min(pool, key=lambda x:x[1])[0]
        
        print("Final Result: " )
        plot_cities([x[1] for x in xa])
        return min(pool, key=lambda x:x[1])[1]

def plot(xAxis,avgX,yAxis):

        '''Matplotlib used to plot graph, Xaxis is generation number,Yaxis is the best/average value'''
        
        
        plt.subplot(211)
        plt.plot(np.unique(xAxis), np.poly1d(np.polyfit(xAxis, yAxis, 1))(np.unique(xAxis)))
        #plt.plot(xAxis, yAxis,linewidth=2.0)
        plt.xlabel('Best till now')
        plt.ylabel('Generation')
        
        plt.subplot(212)
        plt.plot(avgX,yAxis, linewidth=2.0)
        plt.xlabel('Average Till Now')
        plt.ylabel('Generation')
        
        
        plt.show()
        
def mutation(offSpring):
        '''if random value is greater than 0.5, choose insert mutation, otherwise choose swap mutation'''
        if random.random()>0.5:
                offSpring = insertMutation(offSpring)
        else:
                offSpring = swapMutation(offSpring)
        return offSpring

def swapMutation(offSpring):

        '''string manupilation used to swap the offspring indices. If random value is greater than 0.6, than only apply the swap(For each)'''
        o1 = offSpring[0]
        o2 = offSpring[1]
        if random.random()>0.2:
                swap1 = random.randint(0,len(o1)-1)
                swap2 = random.randint(0,len(o1)-1)
                o1 = o1[:min(swap1,swap2)] + [o1[max(swap1,swap2)]] + o1[min(swap1,swap2)+1:max(swap1,swap2)] + [o1[min(swap2,swap1)]] + o1[max(swap1,swap2)+1:]

        if random.random()>0.2:
                swap1 = random.randint(0,len(o2)-1)
                swap2 = random.randint(0,len(o2)-1)
                o2 = o2[:min(swap1,swap2)] + [o2[max(swap1,swap2)]] + o2[min(swap1,swap2)+1:max(swap1,swap2)] + [o2[min(swap2,swap1)]] + o2[max(swap1,swap2)+1:]
                                                                                                                 
        return [o1,o2]

def insertMutation(offSpring):
        '''similar like before, string manipulation is used. Based on random index, the higher index element or the lower index element is made to follow the other element'''
        o1 = offSpring[0]
        o2 = offSpring[1]
        if random.random()>0.2:
                swap1 = random.randint(1,len(o1)-1)
                swap2 = random.randint(1,len(o1)-1)
                if swap1<swap2:
                        o1 = o1[:swap1+1] + [o1[swap2]] + o1[swap1+1:swap2] + o1[swap2+1:]
                elif swap2<swap1:
                        o1 = o1[:swap2] + o1[swap2+1:swap1+1] + [o1[swap2]] + o1[swap1+1:]
        if random.random()>0.2:
                swap1 = random.randint(1,len(o2)-1)
                swap2 = random.randint(1,len(o2)-1)
                if swap1<swap2:
                        o2 = o2[:swap1+1] + [o2[swap2]] + o2[swap1+1:swap2] + o2[swap2+1:]
                elif swap2<swap1:
                        o2 = o2[:swap2] + o2[swap2+1:swap1+1] + [o2[swap2]] + o2[swap1+1:]
        return [o1,o2]
                                                                                                                 
def Crossover(parents):
        '''Crossover to produce offspring'''
        offspring = []
        #Mom is the first element of parent
        mom = parents[0]
        #Dad is the second element of parent
        dad = parents[1]

        #Looped to produce 2 offspring for interchanging mother and father
        for x in range(0,2):

                #exclude Mom contains only the list of cities without the travel cost
                excludeMom = mom[0]

                #exclude Dad contains only the list of cities without the travel cost
                excludeDad = dad[0]
                length = len(excludeMom)

                #As specified in slides, the procedure to produce crossover is run based on random a and b
                a=random.randint(0,length-1)
                b=random.randint(0,length-1)
                
                genesFromMom = excludeMom[min(a,b):max(a,b)]
                
                pickFromDad= max(a,b) % len(excludeDad)
                genesFromDad = []
                for i in range(0,len(excludeDad)):
                        
                        if (excludeDad[pickFromDad] in genesFromMom) == False:
                                genesFromDad.append(excludeDad[pickFromDad])
                        pickFromDad = (pickFromDad + 1) % len(excludeDad)
               
                
                offspring1 = genesFromMom + genesFromDad
                
                offspring.append(offspring1[-min(a,b):length] + offspring1[:-min(a,b)])

                #Mom and dad are interchanged at end of loop
                mom = parents[1]
                dad = parents[0]
        return offspring
