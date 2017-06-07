/* 
 * CS:APP Data Lab 
 * 
 * <ta00263>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */

int bitAnd(int x, int y) {
    
  return ~(~x | ~y);  // '(x' + y') = x.y (x AND y)


}

/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {

 int sum = n;
 sum = sum + sum;
 sum = sum + sum;
 sum = sum + sum; //adding "n" 8 times
 


  return (x >> sum) & 0xFF;  //shifting x by added "n" count to the right since 1 byte is 8 bit, and masking with 11111111

}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    /* x= -16, n = 3*/
    /* x>>3 = -2 */             /*-3*/ /*29*/   
                         /*536870912 = 001000000...*/
                         /*536870912-1 = 00111111 */ 
  return ((x >> n) & ( (1 << ( (~n + 1) + 32)  ) + ~0)); //making normal shift and ANDing it with ((0)*n)1111... e.g if n = 2, 001111....

}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
int  z21  = 0x55555555; // 01
int z22  = 0x33333333; //0011
int  z24 = 0x0F0F0F0F; //00001111
int  z28  =0x00FF00FF; //0000000011111111
int z16 =  0x0000FFFF; //00000000000000001111111111111111
int  z232 = 4294967295; //00..11111111111111111111111111111111
//using hamming weight method,

    x = (x & z21 ) + ((x >>  1) & z21 ); //adding everysecond bit of a, making x the number of 1 in every 2 bits
    x = (x & z22 ) + ((x >>  2) & z22 ); //adding every fourth bit of a, making x the number of 1 in every 4 bit slice
    x = (x & z24 ) + ((x >>  4) & z24 ); 
    x = (x & z28 ) + ((x >>  8) & z28 ); 
    x = (x & z16) + ((x >> 16) & z16); 
   x = (x & z232) + ((x >> 32) & z232);
    return x>>1;
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {


x = ( x >> 16 ) | x; //repeatedly shifts no of "1" in a binary string towards right
x = ( x >> 8 ) | x; //until the "1" shifts at first bit place 
  x = ( x >> 4 ) | x;
  x = ( x >> 2 ) | x;
  x = ( x >> 1) | x;
  // evaluate if any number of "1" is present in "x", if yes, it converts it to 0. if no, then it converts it to "1"
  return ~x & 1;





}









/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {

 int min = ~0<<31;
 //shift "-1" by left 31 times, since we have 32 bit number, this will give 10000..(*32)

  return min;

}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */

int fitsBits(int x, int n) {

                 /* x=-5, n =3*/
    int min = 1<<(n+(~0)); /* min = 4 */
    int negw1 =  ~min + 1; //negw1 = -4
    int max = ~negw1; //max = 3
    //checking x <=max
    int step1 = !((((min) + (~x) )>>31) & 1);
    //checking min<=x
    int step2 = !((((x+1) + (max) )>>31) & 1);
    
    //checking if the number "x" is greater than the negative of 2^n, and lesser than 2^n - 1 
//return 1 if both conditions are true

  return (step1 & step2) ;

}

/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
 
int divpwr2(int x, int n) {
    int les = !((((31) + (~n) )>>31) & 1); //tried to score full marks, but failed.
    int add = (((x>>31)&1)&(!!x)) ;
    return (((x>>n) + add) & (~les+1) ) ;
//right shift the number if positive. if it is negative, add 1 to the final answer.
}

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {


    //negate x and add 1
  return (~x+1);

}

/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
 


int isPositive(int x) {

//checks if the msb of x is 1 or not.
  int easy= (x>>31);
  return (!(easy&1)&(!!x)) ;

}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {


return !((((y+1) + (~x) )>>31) & 1);
//x -y, if positive than x is greater than y, else anser is negative
}








