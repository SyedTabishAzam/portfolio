#include "crypto2.h"
#include <math.h>
#include <stdio.h>
// Other includes as necessary.
#include <iostream>
#include <ctime>
#include <sstream>
#include <stdint.h>
using namespace std;

string converttobinary(int x,int bits);
string binstr_g="";        //declared a global variable to save binary string representation

bool Tools::primality2(unsigned long n, int k) {
  long l(0);
  long j(0);
  long *x = &j;
  long *y= &l; //few variables and pointers declared to be passed to gcd
  
 srand(std::time(0)); //seed given to rand which is the current time
   
  while(k>0){                //loop for number of iterations
 
  int a = (rand() %(n-1))+1;        //generate a random number a
  
  if(gcd(a,n,x,y)!=1){              //if n shares a divisor with a, it is obviously non prime number. hence false returned
                   
                  return false;
                  }
    else{
            
         if(((fastModularExponent(a,n,n)-fastModularExponent(a,1,n)))==0){ //checks if a^n mod n - a mod n = 0, prime is returned if true 
                                                                         
                                 return true;
                                 }
         else if(fastModularExponent(a,n-1,n)==1){ //else if a^n-1 mod n =1, try again with next "a"(this ensures that the code is run for number of recurrence0
              
              k--;
              
              }
         
         }
  
  }
return false; //if all the recurences fail with a same result, composite (false) is returned
}
void Tools::divmod(long a, long b, long* q, long* r) {
  *q = long(a / b); //q points to location of a/b
  
  
  
  *r = (a - (b * (*q)));  //r points to location of a mod b ( a - b * q)
}


long Tools::gcd(long a, long b, long* x, long *y) {

     long s=0;
     long olds=1;
     long t=1;
     long oldt=0;
     long r=b;
     long oldr = a; //declares some variables, to be used as buffer
     while (r>0){   //loop until the gcd is not found
           
           long quotient = long(oldr/r);  //quotient = a /r
           long prov = r;  //a variable prove is the current b
           r = oldr - quotient*prov; //remainder is a-q*b
           oldr = prov; //make oldr, the current b (to bes used as buffer)
           long prov2 = s;   
           s = olds - quotient*prov2;
           olds = prov2;
           long prov3 = t;
           t = oldt - quotient*prov3;
           oldt = prov3;
           }
    
    *y = oldt;
   
    *x = olds;
     
              
     
  return oldr;
}

bool Tools::primality1(unsigned long n) {
  int i,j;
  i=0;
  
  for(int j=2;j<=sqrt(n);j++){ //loops for 2 - sqrt of n times (if n = 25, loop till 2-5) 
                         i=j;//make i, the current j {2,3,4,5}
                         
                         while(i<n){   //for each i {2,3,4,5}
                                    
                                    i = i + j;     //multiply i by 2
                                    if(i==n){      //if any value of "i" is able to get equal to "n" , false is returned
                                             
                                             return false;
                                             }
                                    }
                         }
  //if not, true is returned
  return true;
}



int Tools::random(int n, int l, int s) {
    
  long randomint,rvalue;
  long nextseed;
  
  int seed = s;
  int i;          
  unsigned long long curs=1;         
  for(i=0;i<=n;i++){            //loop till the term needed
                     curs = curs * seed;   //keep multiplying previous seed by current seed. basically i.e seed * seed
                     
                     ostringstream nthterm;
                     nthterm<<curs;            //convert to string, value of current seed
                     string randomstr = nthterm.str();
                     
                     while(randomstr.length()<=l){
                                                  // if currentseed < lenght desired (l), add trailing 0's
                                                 randomstr="0" + randomstr;
                                                 //this function was necassary so that program doesnt output memory error
                                                 }
                     
                     randomstr = randomstr.substr(randomstr.length()-(l+1),l);  //pick number of digits required from the randomstr
                     istringstream(randomstr)>>curs;                              //make it the next seed
                     seed = curs;  
                   }
  
//after n recursions, the nth term is the current seed that is returned
  return curs;
}

unsigned long long non2_g=1; //declared globar variable to multiply powers
unsigned long long Tools::fastModularExponent(int a,unsigned long long b, int c) { //type changed since fastModular can return really long numbers
    // A^2 mod C = (A^1 mod C) * (A^1 mod C)
    
    float checkb = static_cast<float>(b);
    
    while (checkb>1){ //this loop checks if the number is in power of 2. if it is not in power of 2, it would eventually return a floating number when divided multiple times by 
          checkb=checkb/2.0; //so for 8, {8 4 2 1}------for 9{ 9 4.5 2.25 1.125}
           
          }
    
   //if it is in power of 2..
    if(checkb==1){
                  //if b =1 , return a mod c
                  if (b==1){return a%c;}
      // else a variable jk = a^b/2 mod c
       unsigned long long jk = fastModularExponent(a,b/2,c)  ;
       //square jk and return jk mod c
       return (jk*jk)%c;
    }
    else{
         // if number is not in power of 2
         unsigned long bits = long(pow(2,30));
          //convert it to bits 
         string power=converttobinary(b,bits);
         //power now has 2^30 bit representation of b
         int recur;
         
         for(recur=0;recur<power.length();recur++){  //loop for length of power (i.e 30)
                                                   //if the current index position = 1..
                                                   if(power.at(recur)=='1'){
                                                                     //2^the index. so if its at index 4, 2^4 = 16
                                                   non2_g = non2_g%c * fastModularExponent(a,long(pow(2,power.length()-(recur+1))),c);
                                                                        //global non2_g is now equal to its own mod, * a^(2^index)mod  (general rule)
                                                                          }
                                                   }
         }
   
    return (non2_g%c);
    
}  
string converttobinary(int x,int bits){ //helper function
       
       if(x==0){ return binstr_g;} //base case
       
       if (x<bits){  //check for every bit, if number is lesser thn the bit value, put 0 in string
                   
                   binstr_g = "0" + converttobinary(x,bits/2);  //and check again for x with halved bits
                   }
       else{
              binstr_g = "1" + converttobinary(x-bits,bits/2); //if x >= bits, put 1 in string and check for x-bits with halved bits
            }
               
       return binstr_g;
       }

long Tools::stringToNumbers(std::string text) {
     //pretty self explanatory, simply converts the text to its ascii value (method of own choice)
  long i,thevalue;
  stringstream numeric;
  thevalue = 0;
  numeric << "";
  for(i=0;i<text.length();i++){
                               numeric<<int(text.at(i));
                               istringstream(numeric.str())>>thevalue;
                               
                               }
  
  
 
  
  return thevalue;
}  


void Tools::generateKeys(int l, unsigned long* n, unsigned long* e, unsigned long* d) {
srand(time(0));
unsigned int a=rand()%100;
//a is generated from 0-99

int r=1;
int lengthofp1;
long p1 = long(rand()) % (9*long(pow(10,l-1))) + long(pow(10,l-1));
//p1 is a number between (9*(10^l-1)) to (10^l-1)
//so if a l = 4, p1 is a number between 1000 to 9000

while((primality1(p1))==0 ){
                         //keeps adding 1 until p is not prime
                       p1 = p1 + 1;
                       
                        }



long p2 = long(rand()) % (9*long(pow(10,l-1))) + long(pow(10,l-1));
//same case with p2
while((primality1(p2))==0){
                        
                        p2=p2+1;
                
                      
                        
                        }                        


*n= p1*p2;
unsigned long phin= (p1-1) * (p2-1);
unsigned long k = 2;
*e=(rand()%5)+1;
//randomly generates e from 1 - 5 (small)
*d = ((k*phin)+1)/(*e);
//d is calculated
  
}

long Tools::encrypt(long m,unsigned long n, unsigned long e) {
  //since encrypt = m^e mod n where m is message and e is public key
  return fastModularExponent(m,e,n);
}

long Tools::decrypt(unsigned long c, long d,unsigned long n) {
  //since decrypt is c^d mod n where c is ciphertext and d is private key
  return fastModularExponent(c,d,n);;
}

// ----------------------------------------------------------------------

RSA::RSA() {
  Tools _tools;  // member variable - to be used in other methods of this class.
  //private variables declared in header (class)
  mpn=0;
  mpe=0;
  mpd=0;
  n = &mpn;
  e = &mpe;
  d = &mpd;
 _tools.generateKeys(3,n,e,d);

  
}

std::string RSA::encrypt(std::string plainText) {
          


  long value = _tools.stringToNumbers(plainText);
  //value is the int value of string
 long c= _tools.encrypt(value,*n,*e); //this value is encrypted to make the value of c
 ostringstream r;
 r<<c;
  return r.str();
}

std::string RSA::decrypt(std::string cipherText) {
  long value = _tools.stringToNumbers(cipherText);
  //cipher text is converted to int value
 long m= _tools.decrypt(value,*d,*n); //this int value is decrypted to find the orignal message

 ostringstream r;
 r<<m;
  return r.str();
}

