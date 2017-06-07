import csv
import numpy as np
import os
import time
import random
import matplotlib.pyplot as plt
from sklearn import metrics
from sklearn.cluster import KMeans
os.chdir("C:\\Users\\Tabish\\Desktop\\Ass 2b")

def titanicPred():
    #Open training file as csv
    file1 = open("train.csv","r") 
    reader = csv.reader(file1)
    data = []
    for row in reader:
        data.append(row)
    data = np.array(data)
    #Picking every data except header row
    data = data[1:]

    
    
    #returns the array of "true or false" if the survived passenger is or is not a female respectively
    womenSurvived = data[0::,4] == "female"
    menSurvived = data[0::,4] != "female"

    #Masks the data to convert it to 0's and 1's
    totalFemale = data[womenSurvived,1].astype(np.float)
    totalMale = data[menSurvived,1].astype(np.float)

    #np.size returns the size of the array, and astype converts the object to float (previosly string)
    #np.sum returns the sum of all the elements in np array
    #ratio female survived is the propotion of all the females with female survived
    ratioFemaleSurvived = np.sum(totalFemale)/np.size(totalFemale)


    #ratio male survived is the propotion of all the males with female survived
    ratioMaleSurvived = np.sum(totalMale) /np.size(totalMale)


    #if the female ratio is higher than male ratio, then add "0" to male ratio string and "1" to female ratio string
    if ratioFemaleSurvived > ratioMaleSurvived:
        malePred = "0"
        femalePred = "1"
    else:
        malePred = "1"
        femalePred = "0"
    

    #Opening the test file to predict data
    testFile = open("test.csv","r")
    testRead = csv.reader(testFile)

    #opening the prediction file
    predFile = open("genderbasedmodel.csv", "w")
    predWriter = csv.writer(predFile,lineterminator='\n')

    predWriter.writerow(["PassengerId","Survived"])
    firstline = True
    
    for row in testRead:
        if firstline==True:
            firstline=False
            continue
        #If the data is of "female" in test data, then write it to predicted data with string from above evaluated value (0/1)
        if row[3] == "female":
            predWriter.writerow([row[0],femalePred.strip()])
        else:
            #Do same for male
            predWriter.writerow([row[0],malePred.strip()])
    testFile.close()
    predFile.close()


def GenderByVoice():
    file1 = open("voice.csv","r") 
    reader = csv.reader(file1)
    
        
    
   

    

   
    data = []
    target = []
    training = []
    test = []
    firstLine = True
    switch = True

    #Shuffle the data, enter every alternate row in training and test
    for row in reader:
        if firstLine == True:
            firstLine = False
            continue
        if switch == True:
            training.append(row)
            switch = False
        else:
            test.append(row)
            switch = True
       
    #Divides data into train_x and train_y, and test_x
    training = np.array(training)
    test = np.array(test)
    
    train_x = training[0:,0:-1]
    train_y = training[0:,-1]
    
    test_x = test[0:,0:-1]
    test_y = test[0:,-1]

    #Used kmeans clustering to clasify data. 2 clusters model used
    kmeans = KMeans(n_clusters=2, random_state=0).fit(train_x)
    
    #Predicts the data using test x
    predY = kmeans.predict(test_x)
    outY = []

    #Converst 0 and 1 to "male" and "female" respectively
    for i in predY:
        if i==0:
            outY.append("male")
        else:
            outY.append("female")
    

    print("Accuracy is: ", metrics.accuracy_score(outY,test_y))
    
    
    
