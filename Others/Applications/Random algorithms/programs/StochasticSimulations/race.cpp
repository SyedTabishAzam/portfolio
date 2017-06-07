#include "race.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <windows.h>
using namespace std;
// Other includes as necessary.

//int main(int argc, char** argv) {
//    cout << " \n Welcome to the 'Tortoise and the Hare' - an adaptation from Aesop's fables.";
//    schedule();
//    cout << " \n The End.";
//    return 0;
//}
string winning_g = "";
int main(){
    schedule();
 system("PAUSE");
}
void schedule() {
   // your code go here
   int clock;
   clock = 0;
   srand(time(NULL));
   bool stoploop= true;
   int tcurrentposition = 0;
   int hcurrentposition = 0;
   for(clock=0;stoploop==true;clock++){
        displayCurrentPositions(clock,tcurrentposition,hcurrentposition);
        delay();
        tcurrentposition = returnTortoisePosition(tcurrentposition);
        hcurrentposition = returnHarePosition(hcurrentposition);

         if (winning_g == "true"){
                     announceWinner(tcurrentposition,hcurrentposition);
                     stoploop = false;
                     }

         }

}

void displayCurrentPositions(int tick, int tortoisePos, int harePos) {
    // your code go here
     tortoisePos = tortoisePos / 2;
     harePos = harePos / 2;
    if (tortoisePos<MinPos){tortoisePos=MinPos;}
    if (tortoisePos>MaxPos){tortoisePos=MaxPos + 1;}
    if (harePos<MinPos){harePos=MinPos;}
    if (harePos>MaxPos){harePos=MaxPos + 1;}

   string tryout ="";
   string distance = "";
   for(int sp=0;sp<47;sp=sp+1){
        distance = distance + " ";
        }
   distance = distance + "F";
   string tor="T";
   string har = "H";
   if (tortoisePos==harePos){
        distance.replace(tortoisePos,1,"U");
        }
   else{
   if (tortoisePos<47){
      distance.replace(tortoisePos,1,tor);
   }
   else{
        distance = distance + tor;
        winning_g = "true";
        }

   if (harePos<47){
      distance.replace(harePos,1,har);
   }
   else{
        distance = distance + har;
        winning_g = "true";
        }
    }

    cout<<"Time: "<<tick<<distance<<endl;
}

int returnTortoisePosition(int currentPosition) {
    // your code go here
    map<string,int> stepsmap;
    stepsmap["snooze"]=0;
    stepsmap["slide"]=-12;
    stepsmap["hippetyhop"]=9;
    stepsmap["hop"]=1;
    stepsmap["slip"]=-2;

    double worked = returnUniformRandomNumber();
    float inDecimals = worked / 100;
    string action;
        if ((inDecimals>0) && (inDecimals<=0.2)){
            action = "snooze";
            }
        else if( (inDecimals>0.2 && inDecimals<=0.4) ){
            action = "hippetyhop";
            }
        else if( (inDecimals>0.4 && inDecimals<=0.5) ){
            action = "slide";
            }
        else if( (inDecimals>0.5) && (inDecimals<=0.8) ){
            action = "hop";
            }
        else if( (inDecimals>0.8 && inDecimals<=1.0) ){
            action = "slip";
            }
        return (currentPosition + stepsmap[action]);
}

int returnHarePosition(int currentPosition) {
    // your code go here
    map<string,int> stepsmap;
    stepsmap["brisk"]=3;
    stepsmap["slip"]=-6;
    stepsmap["slowwalk"]=1;
    double worked = returnUniformRandomNumber();
    float inDecimals = worked/100;
    string action = "";
     if ((inDecimals>0) && (inDecimals<=0.5)){
              action = "brisk";
                     }
        else if( (inDecimals>0.5 && inDecimals<=0.7) ){
             action = "slip";

             }
        else if( (inDecimals>0.7 && inDecimals<=1.0) ){
             action = "slowwalk";
        }
        return (currentPosition + stepsmap[action]);
}

void announceWinner(int tortoisePos, int harePos) {
    //your code go here

    if (tortoisePos>harePos){
    cout<<"The tortoise wins!"<<endl;
    }
    else{
         cout<<"The hare wins!"<<endl;
         }

}

inline double returnUniformRandomNumber(){
	// your code go here
    double u = rand() % 100 + 1;
    return u;

}
inline void delay(){
	// your code go here
	Sleep(200);
}


