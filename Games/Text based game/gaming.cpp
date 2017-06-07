#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class node{
      private:
              int m_probability;  //private member variable to store the location of the ship
      public:
             node(int p){
                    m_probability=p;
                    }
             string getAttrib(){
                    int gen;
                    if(m_probability == 1 | m_probability==4 | m_probability==7){    //If the ship is on middle row
                    double val = (double)rand() / RAND_MAX;    //generate a decimal value lesser than 1
                    int random;
                    if (val < 0.33)       //  33%                         //33 % chance given for gen to be 0
                        gen = 0;
                    else if (val < 0.66)  //  33% + 33%                        //33 % chance given for gen to be 1
                        gen = 1;
                    else if (val < 1)  //  33% + 33% + 33%                     //33 % chance given for gen to be 2
                        gen = 2;
                    }
                    if(m_probability == 0 | m_probability==3 | m_probability==6){ // if the ship is on left row
                    double val = (double)rand() / RAND_MAX;
                    int random;
                    if (val < 0.20)       //  20%          //similar chances given to gen as above
                        gen = 0;
                    else if (val < 0.40)  //  20% + 20%
                        gen = 1;
                    else if (val < 1)  //  20% + 40% + 60%
                        gen = 2;
                    }
                     if(m_probability == 2 | m_probability==5 | m_probability==8){ // same for the ship when on right row with different chances
                    double val = (double)rand() / RAND_MAX;
                    int random;
                    if (val < 0.40)       //  40%
                        gen = 0;
                    else if (val < 0.80)  //  40% + 40%
                        gen = 1;
                    else if (val < 1)  //  20% + 40% + 40%
                        gen = 2;
                    }
                    if(gen==0){ return "enemy ship";} //depending on variable gen, the file determines if the returned thing on location is enemy friend or puzzle
                    else if(gen==1){return "friend ship";}
                    else if(gen==2){return "puzzle";}
                    }
      
      };
      
class ship{ // class for ship
      private:
              int m_health;// ships health
              int m_level;    //ships level, determined by location it is standing on
              string m_name;  //ships name
      public:
      ship(string name){      
             m_name = name;   
             m_health = 100; //health initialized to 100%
            
             m_level = 1;    //level is now 1
             }
      string getGun(int gunp){              //depending on gunp, the gun of the ship is returned ( to be used by enemy ship )
             if(gunp==0){return "Rock";}
             else if(gunp==1){return "Water";}
             else if(gunp==2){return "Fire";}
             }
     int getHealth(){ //Health getter

         return m_health;        
                 }
     
     int getLevel(){             //level getter
         return m_level;
         }
     void setHealth(int health){ //health setter
          m_health = health;
          }
     void setLevel(int level){   //level setter
          m_level = level;
          }
     string getName(){    //name getter
            return m_name;
            }

      };
void grid(int position);         //forward declarations
void game(ship &our);
void move(ship &our,int option);
bool puzzle();

void initialize(){ //game initializer
     
     cout<<"Starting Game"<<endl;
     cout<<"Please enter your ship name: ";
     string name;
     getline(cin,name); //inputs ship name
     ship our(name); //make a new object of type ship with the given name
     cout<<"Welcome to the world of Darkness "<<our.getName()<<endl;
     cout<<"Your Mission is to reach till end. You will encounter Enemy, Friend or Puzzle on each location"<<endl;
     cout<<"       X        "<<endl<<endl;
     grid(11);     //grid for game.
     game(our); //game function made, and our ship is passed to it
     }
     
void grid(int position = 10){
     int count = 0;
     string pos;
     string tr;
     
     for(int row=0;row<3;row++){ //rows and columns of 3 by 3 made
             for(int col=0;col<3;col++){
                     if(position==count){ 
                                         
                                         cout<<"  X  ";} // if x is standing on a location,instead of the location number, x is printed
                                         
                     else{
                     cout<<"  "<<count<<"  "; // else the location number is printed
                     }
                     count++; 
                     }
             cout<<endl<<endl;
     }
     
     cout<<pos;
     if(position==9){cout<<"      |X|       "<<endl<<endl;} //if the ship reaches the end, print this kind of output 
     else{
     cout<<"      | |       "<<endl<<endl;} //else print normal output
}

void game(ship &our){       //game funct
     int selection = 0;
     int ll = 0;
     int option;
     bool canend =false;
     while(our.getHealth()>0 && (canend==false)){ //keep running the game until ur health is not 0, or you havent reached the end
                             
                              if(our.getLevel()==1){     //if ship level is 1, that means u are only allowed to go on first column i.e 0 1 2
                              cout<<"select 0 1 2"<<endl;
                              selection = 3;
                              ll = 0;              
                              }
                              else if(our.getLevel()==2){
                                   cout<<"select 3 4 5"<<endl;
                                   selection = 6; 
                                   ll=3;
                                   }
                              else if(our.getLevel()==3){
                                   cout<<"select 6 7 8"<<endl;
                                   selection = 9;
                                   ll=6;
                                   }
                              else if(our.getLevel()>3 && option!=7){
                                   cout<<"You need to go to location 7 in order to end!"<<endl;
                                   selection = 9;
                                   ll=6;
                                   }
                              else if(option==7){ //you can only reach the end through location 7
                                   cout<<"You can end the game now, press 9"<<endl;
                                   selection = 99;
                                   ll = 8;
                                   }
                              
                              cin>>option;
                                  while((option>=selection) | (option<ll) ){  //if you enter wrong location, you are promt again
                                                           cout<<"No! You cant go there yet!"<<endl;
                                                           cout<<"Select other valid location"<<endl;
                                                           cin>>option;
                                                           }
                                  if(option==9){canend=true; our.setHealth(0); break;} //when u pass location 7, u can win
                                  move(our,option); //considering ur next chosen location, u can now move
                                 
                                 }
     cout<<"Game Over"<<endl;//once the loop breaks, this is printed
     if(bool(canend)){cout<<"You won!"<<endl;} //if u win by reaching end, you get you won output
}
void fight(ship &our){  //fight function when encountered by enemy ship
     ship enemy("Enemy");
     cout<<"You need to fight this ship in order to proceed"<<endl;
     cout<<"Try your luck, and choose a gun?"<<endl;
     cout<<"Rock , Fire , Water"<<endl;
     string og;  //you choose your gun
     cin>>og;
     int gunRan = rand()%3; //random number is chosen between 0 to 2
     string eg =enemy.getGun(gunRan); //enemy gun is then chosen at random
     while(eg==og){ // if you both select same gun
                eg =enemy.getGun(rand()%3); // you play again
                cout<<"You both used same gun, no effect"<<endl;
                cout<<"Try your luck, and choose a gun?"<<endl;
                cout<<"Rock , Fire , Water"<<endl;
                cin>>og;
                }
     if(eg=="Fire" && og=="Water"){ //Your gun is compared with enemy's gun
                   cout<<"Enemy chose Fire and evaporated your water"<<endl;
                   our.setHealth(our.getHealth()-50);
                   cout<<"New Health: "<<our.getHealth()<<endl;
                   }
     if(eg=="Water" && og=="Rock"){
                    cout<<"Enemy chose Water and softened your Rock"<<endl;
                   our.setHealth(our.getHealth()-50);
                   cout<<"New Health: "<<our.getHealth()<<endl;
                   
                   }
     if(eg=="Rock" && og=="Fire"){
                   cout<<"Enemy chose Rock and put out your Fire"<<endl;
                   our.setHealth(our.getHealth()-50);
                   cout<<"New Health: "<<our.getHealth()<<endl;
                   }
     if(eg=="Fire" && og=="Rock"){
                   cout<<"You defeated Enemy's fire using your Rock weapon, you can proceed"<<endl;
     
                   }
      if(eg=="Water" && og=="Fire"){
                     cout<<"You put out your Enemy's fire, you can proceed"<<endl;
                     }
       if(eg=="Rock" && og=="Water"){
                     cout<<"Your Water gun softened your enemy's Rock gun, you can proceed"<<endl;
                     
                     }
     
     
     }
void move(ship &our,int option){ //function to move the ship on next location
     
     
     node n(option); //each location is a new node
     bool pass=true; 
     string encounter = n.getAttrib(); //each node has an attrib , encounter variable stores that attrib
     cout<<"You have encountered "<<encounter<<" in this position"<<endl;
     if(encounter=="enemy ship"){  //if you encounter enemy ship, you fight
                              fight(our);
                              if(our.getHealth()>0){ //if you win the fight, you get level ++
                                                    our.setLevel(our.getLevel()+1);
                                                    }
                              }
     else if(encounter=="friend ship"){ //if you encounter friendship, you simply gain 25 % health and increase in level
          cout<<"You got an upgrade on your health"<<endl;
          our.setHealth(our.getHealth() + 25);
          cout<<"New Health: "<<our.getHealth()<<endl;
          our.setLevel(our.getLevel()+1);
          }
     else if(encounter=="puzzle"){ //if you encounter puzzle, you need to solve it
          
          pass=puzzle();
                             if(pass==false){ //if you cant solve it, you lose straightaway
                                             cout<<"You lost";
                                             }
                                             else{our.setLevel(our.getLevel()+1);}
                             }
          
          
     if(pass==true){ //if you lost the puzzle, you lose the game
     grid(option);
     }
     else{our.setHealth(0);}
     
     
     
     
}
     
bool puzzle(){
     ifstream infa("puzzle.txt"); //opens file where you have your puzzles
     int num=-1;
     string lin;
     while(infa){ //count the lines in this file
                num++;
                getline(infa,lin);
                }
     infa.close(); //closes the file
     ifstream inf("puzzle.txt");//and reopens it to get the cursor to the first line
     int puz = (rand()%num); // random number is generated from 0 to no of line of the puzzle file
     string lin2;
     for(int i=-1;i!=puz;i++){ //every line upto that number is flushed
             getline(inf,lin2);
             }
     cout<<lin2<<" "<<endl; //the riddle on THAT PARTICULAR line is asked
     
     ifstream ans("answer.txt"); // opens the answer file
     string correct;
     for(int j=-1;j!=puz;j++){ //gets the same line on the answer file (this line has the answer to the corresponding line of puzzle)
             getline(ans,correct);
             }
     cout<<"Please give the correct answer to proceed to the selected point"<<endl;
     string compare;
     cin>>compare;
     if(compare==correct){return true;} //if the input answer is the same as the answer in the answer file, true is returned
     else{return false;}
     }
     
int main(){
    srand(time(NULL)); //seeds the random generation
    initialize(); //initializes the game
  system("PAUSE");
 return 0;   
}


