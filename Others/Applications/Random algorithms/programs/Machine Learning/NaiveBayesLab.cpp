// reading a text file
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

//Loads data from CSV file to arrays
void LoadData(string fileName,vector<vector<string> > &d)
{
	string line;
	
	ifstream myfile (fileName.c_str());

	if (myfile.is_open())
	{
		getline (myfile,line) ; //skip first line
		int row =0;
		
		while ( getline (myfile,line) )
		{
			std::vector<std::string> elems;
		  std::vector<std::string> x = split(line, ',',elems);
		  
		  d.push_back(x);
		  
		  row++;
		}
		myfile.close();
	}
	
	else cout << "Unable to open file"; 
	}
vector<string> retrieveLabels(vector<vector<string> > &td){
     //td[rows][columns]
     //td.size()==Row size
     //td[row].size()== Colum size
     vector<string> rl;
     vector<string>::iterator it;
     bool flag=true;
     
     for(int i=0;i<td.size();i++){ //iterate thru csv file for rows
             it = rl.begin();      //it points to begining of rl 
             flag=true;
             for(it = rl.begin();it!=rl.end();it++){        //iterate through rl vector
                    if(*it==(td[i][td[i].size()-1])){ //if value of rl matches the value of class label, that means its already there
                        flag= false;
                    }
             }
             if (flag==true){                              //if value was not found in rl vector
                 rl.push_back((td[i][td[i].size()-1]));   //add it to rl vector
             }
             
     }
     
     return rl;
}
float computePrior(vector<vector<string> > &td,string classLabel){
    //iterate thru last row
    //count all classlabels
    //after iteration, divide it by the total rows
    float count=0;
    float totalElements = static_cast<float>(td.size());
    for(int i = 0;i<td.size();i++){
            if((td[i][td[i].size()-1])==classLabel){
                                                    count++;
                                                    }
            }
    return (count/totalElements);
    
}
float computeConditional(vector<vector<string> > &td,int colIndex, string colValue, string classLabel){
      float count;
      float count2;
      
      for(int i=0;i<td.size();i++){ //iterate through every row
              if((td[i][colIndex]==colValue) && (td[i][td[i].size()-1]==classLabel)){      //count all values in index that have common class label
                                             count ++;
                                             }
              if((td[i][colIndex]==colValue)){
                                              count2++;
                                              
                                              }
              }
      
      return (count/count2);
      }

float computePosterior(vector<vector<string> > &td,vector<string> recs, string classLabel){
      vector<string>::iterator it;
      it=recs.begin();
      float var1;
      float var2;
      int column = 0;
      var2=1;
      var1=computePrior(td,classLabel);
      for(it=recs.begin();it!=recs.end();it++){
                                               
                                               var2 = var2 * computeConditional(td,column,*it,classLabel);  
                                               column++;                                
                                               }
      return var2*var1;
      }

string predict(vector<vector<string> > &td,vector<string> recs){
       
       vector<string> labels;
       float highest = 0;
       string max;
       labels = retrieveLabels(td);
       vector<string>::iterator it;
       it=labels.begin();
       for(it=labels.begin();it!=labels.end();it++){
                                                    if (highest<computePosterior(td,recs,*it)){
                                                                             highest = computePosterior(td,recs,*it);
                                                                             max = *it;                  
                                                                                               }                                              
                                                    }
       return max;
       }
void compute(vector<vector<string> > &td,vector<vector<string> > &filetotest){
     
     string pvalue;
     float a,c,ac;
     float ev=0;
     float av=0;
     float f=0;
     float fpre=0;
     
     for(int i=0;i<10;i++){
         vector<string> row;
         for(int ix=0;ix<filetotest[i].size();ix++){
                 row.push_back(filetotest[i][ix]);        
                 }
         string pvalue = predict(td,row);
         if(pvalue==(filetotest[i][filetotest[i].size()-1])){
             ev++;
         }else{
              av++; 
               } 
          if((td[i][td[0].size()-1])=="e" ){
                                                     c++;
                                                     if((filetotest[i][filetotest[i].size()-1])=="e"){
                                                                                                  a++;
                                                                                                  }
                                                     }
        else{
             if((filetotest[i][filetotest[i].size()-1])=="e"){
                                                          ac++;
                                                          }
             }
     }
     
     
     cout<<"Accuracy is "<<ev/(av+ev)<<endl;
     cout<<"Precision is "<<(a)/(c)<<endl;
     cout<<"Recall is "<<a/(ac+a)<<endl;
     
     }
int main () {
  
  //Load training data
  vector<vector<string> > trainingData;
  LoadData("MushroomTraining.csv", trainingData);

  cout<<"Number of rows in training Data:"<<trainingData.size()<<endl;
  if (trainingData.size() > 0)
  	cout<<"Number of cols in training Data:"<<trainingData[0].size()<<endl;

  //Load test data	
  vector<vector<string> > testData;
  LoadData("MushroomTest.csv", testData);

  cout<<"Number of rows in test data:"<<testData.size()<<endl;
  if (testData.size() > 0)
  	cout<<"Number of cols in test data:"<<testData[0].size()<<endl;
 	//retrieveLabels(trainingData);
 	vector<string> recs;
  compute(trainingData,testData);
  system("PAUSE");
  return -1;
}
  

