import numpy as np
import cv2
import os
import csv
from PIL import Image
import dlib
import numpy as np
import glob
from shutil import copyfile
import random
import math
from scipy import spatial
import sklearn
from sklearn import cross_validation
from sklearn import tree
from sklearn.tree import DecisionTreeClassifier
from sklearn import metrics
from sklearn import preprocessing
from sklearn import linear_model
from sklearn.naive_bayes import GaussianNB
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import LinearSVC
from sklearn.calibration import calibration_curve

pathTest = "training-images\\Test"
pathTrain = "training-images\\Train"

cascadePath = "haarcascades\\haarcascade_frontalface_default.xml"
faceCascade = cv2.CascadeClassifier(cascadePath)
students = []
recognizer = cv2.createLBPHFaceRecognizer()

def readList():
    csvfile = open("training-images/list.csv")
    formatedFile = csv.reader(csvfile,delimiter=',',quotechar="|")
    for row in formatedFile:
        students.append(row)
    csvfile.close()


def LiveRecognize():
    recognizer.load("tData.yml")
    if len(students)==0:
        readList()
    cam=cv2.VideoCapture(0)
    font=cv2.cv.InitFont(cv2.cv.CV_FONT_HERSHEY_PLAIN,1,2,0,4)
    while (True):
        ret,image=cam.read();
        image=cv2.flip(image,1)
        gray=cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
        #faces=faceCascade.detectMultiScale(gray,1.3,5)
        faces = faceCascade.detectMultiScale(gray,scaleFactor = 1.2,minNeighbors=5,minSize=(30,30))
        if(cv2.waitKey(1)==ord('s')):
            name =raw_input("Enter name: ")
            uid = raw_input("Enter id: ")
            insertToList(name,uid)
            cv2.imwrite(os.path.join("training-images\\train",name + ".png"),image)
            
        for (x,y,w,h) in faces:
            cv2.rectangle(image,(x,y),(x+w,y+h),(0,0,255),2)
            nbPred,conf = recognizer.predict(gray[y:y+h,x:x+w])
            stId = str(nbPred)
            inText = [names[0] for names in students if stId in names[1]][0]
            
            cv2.cv.PutText(cv2.cv.fromarray(image),inText + " "+ str(conf),(x-(w/2),y+h+30),font,(0,255,0))
        
        
        cv2.imshow("Face",image)
        if(cv2.waitKey(5)==ord('q')):
            break
    cam.release()
    cv2.destroyAllWindows()
    
def insertToList(name,uid):
    for x  in students:
        if x[1] == uid:
            if min(x[0].lower(),name.lower()) in max(x[0].lower(),name.lower()) == False:
                print("Error! Two faces of same ID found")
            else:
                print("Face already in list. Adding only to learner")
                return
    csvfile = open("training-images/list.csv",'a')
    formatedFile = csv.writer(csvfile)
    formatedFile.writerow([name] + [uid])
    students.append([name]+[uid])
    csvfile.close()
        
        
def train(pathTrain):
    if(len(students)==0):
        readList()
    images,labels = get_images_and_labels(pathTrain)
    cv2.destroyAllWindows()
    
    #training
    recognizer.train(images,np.array(labels))
    recognizer.save("tData.yml")
    print("Recognize saved as tData.yml")
    
def get_images_and_labels(path):
    
	
    image_path = [os.path.join(path,f) for f in os.listdir(path)]
    

    images = []
    count = 0
    labels = []
    
    for ipath in image_path:
        image_pil = Image.open(ipath).convert('L')
        
        image = np.array(image_pil,'uint8')
       
        studentName = os.path.split(ipath)[1].split(".")[0]
        #print("Found: " studentName.upper())
        print(studentName)
        stId = [x[1] for x in students if min(x[0].lower(),studentName.lower()) in max(x[0].lower(),studentName.lower())][0]
        stId = int(stId[2:])
        faces = faceCascade.detectMultiScale(image,scaleFactor = 1.2,minNeighbors=5,minSize=(30,30))
        print(studentName)
        for (x,y,w,h) in faces:
            images.append(image[y:y+h,x:x+w])
            labels.append(stId)
            #cv2.imshow("Adding faces to training set...",image[y:y+h,x:x+h])
            #cv2.waitKey(50)
    
    return images,labels

def test(pathTest):
    recognizer.load("tData.yml")
    if(students==[]):
        readList()
    #testSet
    ipath = [os.path.join(pathTest, f) for f in os.listdir(pathTest)]
   
    for i in ipath:
        predictImage = Image.open(i).convert('L')
        predictImageNp=np.array(predictImage,'uint8')
        faces = faceCascade.detectMultiScale(predictImageNp,scaleFactor = 1.2,minNeighbors=5,minSize=(30,30))
        print("Found " + str(len(faces)) + " faces in "+i)
        for (x,y,w,h) in faces:
            nbPred,conf = recognizer.predict(predictImageNp[y:y+h,x:x+w])
            stId = str(nbPred)
            
            nbActual = os.path.split(i)[1].split(".")[0].lower()
            inText = [names[0] for names in students if stId in names[1]][0]
            if min(nbActual,inText.lower()) in max(nbActual,inText.lower()):
                print(nbActual + " Recognized with confidence " + str(conf))
            else:
                print(nbActual + " Incorrectly recognized as " + str(nbPred))
            cv2.imshow("Recognizing face",predictImageNp[y:y+h,x:x+w])
            cv2.waitKey(1000)
    cv2.destroyAllWindows()                                     


def runAll(live=True,learn=False):
    '''Use live (boolean) to initiate webcame and live recognization.
    Use learn to learn the model, if learn==false, then previously learn model will
    be used'''
    print("Using list to compare name with student Id")
    readList()
    if(learn):
        print("Using Path: " + pathTrain + " to Train")
        train(pathTrain)
    print("Using recognizer tData.yml")
    if (live==True):
        print("Initiating live webcame to recognize face")
        LiveRecognize()
    else:
        print("Using Path:" + pathTest + " to Test")
        test(pathTest)

#-----------------------SUMBUL--------------#
        
faceDet = cv2.CascadeClassifier("haarcascades\\haarcascade_frontalface_default.xml")
faceDet2 = cv2.CascadeClassifier("haarcascades\\haarcascade_frontalface_alt2.xml")
faceDet3 = cv2.CascadeClassifier("haarcascades\\haarcascade_frontalface_alt.xml")
faceDet4 = cv2.CascadeClassifier("haarcascades\\haarcascade_frontalface_alt_tree.xml")

detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")



def get_landmarks(image):
    landmarks=[]

    detections = detector(image, 1)
    
    for k,d in enumerate(detections): #For all detected face instances individually
        shape = predictor(image, d)

        for i in range(0,68): #Store X and Y coordinates in two lists
            landmarks.append(float(shape.part(i).x))
            landmarks.append(float(shape.part(i).y))
            cv2.rectangle(image,(shape.part(i).x,shape.part(i).y),(shape.part(i).x+1,shape.part(i).y+1),(0,255,255),2)
            
    if len(detections) > 0:
        return landmarks
    else: #If no faces are detected, return error message to other function to handle
        landmarks = []
        return landmarks

def predictCam(image, model):
    emotions = ["neutral", "anger", "contempt", "disgust", "fear", "happy", "sadness", "surprise"]
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    
    face = faceDet.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=10, minSize=(5, 5), flags=cv2.CASCADE_SCALE_IMAGE)
   
    if len(face)!=1:
        return

    for (x, y, w, h) in face: #get coordinates and size of rectangle containing face
        posx=x
        posy=y
        gray = gray[y:y+h, x:x+w] #Cut the frame to size
        out = cv2.resize(gray, (350, 350)) #Resize face so all images have same size
        
    landmarks=get_landmarks(out)
    if landmarks!=[]:
        y_predict=model.predict([landmarks])
        return (emotions[int(y_predict)] , posx , posy)







def Webcam(model,debug = False):
    video_capture = cv2.VideoCapture(0)
    emotions = ["neutral", "anger", "contempt", "disgust", "fear", "happy", "sadness", "surprise"]
    font = cv2.FONT_HERSHEY_SIMPLEX
    recognizer.load("tData.yml")
    if len(students)==0:
        readList()
    font2=cv2.cv.InitFont(cv2.cv.CV_FONT_HERSHEY_PLAIN,1,2,0,4)
    count = 10
    st = ""
    picCounter = 0
    keepSaving = False
    name = ""
    uid = ""
    msg = ""
    while True:
        ret, frame = video_capture.read()
        image=cv2.flip(frame,1)
        gray=cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
        
        count = count + 1
        faces = faceCascade.detectMultiScale(gray,scaleFactor = 1.2,minNeighbors=5,minSize=(30,30))

      
        if(cv2.waitKey(1)==ord('s')):
            keepSaving = True
            name =raw_input("Enter name: ")
            uid = raw_input("Enter id: ")
            insertToList(name,uid)
        if(keepSaving):
            cv2.imwrite(os.path.join("training-images\\train",name+str(picCounter) + ".png"),image)
            picCounter = picCounter + 1
            if picCounter ==10:
                print("Wait while we train")
                train(pathTrain)
                print("Training complete")
                picCounter = 0
                keepSaving = False
                
        if(count==11):
                p=predictCam(image,model)
                count = 0
                if p != None:
                    st = p[0]
        for (x,y,w,h) in faces:
            

            cv2.rectangle(image,(x,y),(x+w,y+h),(0,0,255),2)
            nbPred,conf = recognizer.predict(gray[y:y+h,x:x+w])
            out = cv2.resize(image, (350, 350))


            if (debug==True):
                faceMark = predictor(gray, dlib.rectangle(x,y,x+w,y+h))
                for i in range(0,68): 
                    cv2.rectangle(image,(faceMark.part(i).x,faceMark.part(i).y),(faceMark.part(i).x+1,faceMark.part(i).y+1),(0,255,255),2)
                
            stId = str(nbPred)
            inText = [names[0] for names in students if stId in names[1]][0]
            cv2.cv.PutText(cv2.cv.fromarray(image),inText + " "+ str(conf),(x-(w/2),y+h+30),font2,(0,255,0))

                
            if st=="happy":
                msg = "We can do nothing since you are already Happy"
            if st=="sadness":
                msg = "Bad things happen!, Dont be Sad"
            if st=="disgust":
                msg = "You are rude for being disgusted by me"
            if st=="fear":
                msg= "Dont be affraid! I dont bite"
            if st=="suprise":
                msg = "Suprise! Didnt expect this huh?"
            if st=="neautral":
                msg = "Dont be so awkwardly neautral! You are boring"
            if st=="contempt":
                msg = "Dont show your contempt by doing it very badly"
            
            cv2.putText(image,msg,(30,30), font, .5,(255,255,255),2)
            
        cv2.imshow("image", image) #Display the frame

        if cv2.waitKey(1) == ord('q'): #Exit program when the user presses 'q'
            break
    cv2.destroyAllWindows()
        

def generatedata1(fileX):
    x=[]
    y=[]
    with open(fileX, 'r') as csvfile:
        reader = csv.reader(csvfile, delimiter='\n', quotechar='|')
        for row in reader:
            if row!=[]:
                for line in csv.reader(row, skipinitialspace=True):
                    line=list(map(float, line))
                    x.append(line[:-1])
                    y.append(line[-1])
  

    return (x,y)

def learnModel(data, rand, modelnum):
    X=data[0]
    y=data[1]
    X_train, X_test, y_train, y_test =  cross_validation.train_test_split(X, y, test_size=0.33, random_state=rand)
    models=[tree.DecisionTreeClassifier(),LogisticRegression(),GaussianNB(),LinearSVC(C=1.0),RandomForestClassifier(n_estimators=100)]
    mod=models[0]
    mod.fit(X_train,y_train)
    return mod
    


def Setup(Train=False,debug=False):
    if(Train):
        print("Training model now")
        train(pathTrain)
    if(students == []):
        readList()
    print("Initializing, Please wait")
    readFromList = generatedata1('xy.csv')
    print("Training Mood Data")
    model = learnModel(readFromList,100,0)
    print("Model training complete")
    Webcam(model,debug)
