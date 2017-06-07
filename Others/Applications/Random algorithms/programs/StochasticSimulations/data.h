/* "Include guard" - prevents this file from getting included more
   than once. */  
#ifndef DATA_H
#define	DATA_H

// Userdefine type Data to represents a customer 
typedef struct Item {
    int personID; 
    int arrivalTime;
    int serviceTime;
    int serviceBeginTime;
    int departureTime;
} Data;

#endif  /*DATA_H */
