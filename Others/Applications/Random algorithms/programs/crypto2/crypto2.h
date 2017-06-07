/* "Include guard" - prevents this file from getting included more
   than once. */
#ifndef __CRYPTO2_H_INCLUDED__   
#define __CRYPTO2_H_INCLUDED__ 

#include <string>
/* Resources on std::string:
   http://www.cplusplus.com/reference/string/string/
   http://en.cppreference.com/w/cpp/string/basic_string
*/

/* Provides functions needed for RSA encryption. */
class Tools {
public:
  
  /* Calculates the quotient and remainder using the Quotient Remainder
     theorem.

     Parameters:
     a: the dividend
     b: the divisor
     q: contains the quotient when the function completes execution
     r: contains the remainder when the function completes execution

     Return:
     None
  */
  void divmod(long a, long b, long* q, long* r);

  /* Calculates the Greatest Common Divisor and co-efficients using
     extended Euclidean algorithm.

     Given two numbers, A and B, the algorithm finds, Q, their GCD, and
     X and Y such that: Q = AX + BY

     Parameters:
     a: one of the numbers whose gcd is to be computed
     b: the other number whose gcd is to be computed
     x: contains the coefficient of a when the function completes execution
     y: contains the coefficient of b when the function completes execution

     Return:
     gcd(a,b)
  */
  long gcd(long a, long b, long* x, long *y);

  /* Tests whether a number is prime using divison by numbers up to n.

     Parameters:
     n: number to check

     Return:
     True if n is prime, False otherwise.
  */
  bool primality1(unsigned long n);

  /* Tests whether a number is prime using Fermat's little theorem.

     Parameters:
     n: number to check
     k: number of iterations of Fermat's theorem

     Return:
     True if n is prime, False otherwise.
  */
  bool primality2(unsigned long n, int k);

  /* Generates pseudo-random numbers using the middle square method.

     A series of pseudo-random numbers are generated using the
     seed. The seed is the 0th term of the series. The function
     returns the n-th term.

     Parameters:
     l: the desired length on the the pseudo-random numbers
     n: the desired term number in the series of pseudo-random numbers
     s: a seed number to start the generator

     Return:
     The n-th pseudo-random number.

     Resources:
     Middle square method: https://www.khanacademy.org/computing/computer-science/cryptography/crypt/v/random-vs-pseudorandom-number-generators
     Integer to string: http://en.cppreference.com/w/cpp/string/basic_string/to_string
     Integer to string: http://www.cplusplus.com/reference/cstdlib/itoa/
  */
  int random(int n, int l, int s);

  /* Calculates the exponent with respect to a modulus.

     Exponents can be computed quickly as follows:
     A^2 mod C = (A^1 mod C) * (A^1 mod C) 
     A^4 mod C = (A^2 mod C) * (A^2 mod C) 
     A^8 mod C = (A^4 mod C) * (A^4 mod C) 
     and so on.

     Parameters:
     a: the base
     b: the exponent, >0
     c: the modulus, >0

     Return:
     a^b mod c

     Resources:
     Fast Moudlar Exponentiation: https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/fast-modular-exponentiation
  */
unsigned long long fastModularExponent(int a, unsigned long long b, int c);

  /* Converts a string to a numeric value.

     Use any method of your choice.

     Parameters:
     text: the string to be converted

     Return:
     The numeric represenation of text.

     Resources:
     ASCII table: http://www.asciitable.com
     An example: http://doctrina.org/How-RSA-Works-With-Examples.html#a-real-world-example
  */
  long stringToNumbers(std::string text);


  /* RSA Resources:
   
     Definition: https://en.wikipedia.org/wiki/RSA_(cryptosystem)
     Video Explanation: https://www.khanacademy.org/computing/computer-science/cryptography/modern-crypt/v/the-fundamental-theorem-of-arithmetic-1
     With examples: http://doctrina.org/How-RSA-Works-With-Examples.html
  */

  /* Generates public and private RSA keys.

     The public key is the pair (n,e) where n is the modulus and e is
     the exponenet. The private key is d, the modular inverse of e
     modulus n.

     Parameters:
     l: length of the prime numbers to be used in key generation.
     n: contains the pulic key modulus after the function completes execution.
     e: contains the pulic key exponent after the function completes execution.
     d: contains the private key after the function completes execution.

     Return:
     None
  */
  void generateKeys(int l, unsigned long* n, unsigned long* e, unsigned long* d);

  /* Performs RSA encryption with a public key (n,e)

     Parameters:
     m: given number (message)
     n: public key modulus
     e: public key exponent

     Return:
     RSA encryption of m using (n,e)
  */
  long encrypt(long m,unsigned long n, unsigned long e);

  /* Performs RSA decryption with a private key, d.

     Parameters:
     c: given number (ciphertext)
     d: private key

     Return:
     RSA decruption of c using d.
  */
  long decrypt(unsigned long c, long d,unsigned long n);
};

// ----------------------------------------------------------------------

/* Performs RSA encryption and decryption on strings. */
class RSA {
public:
  /* Constructor - intializes keys and a Tools instance for use in
     other class methods. */
  Tools _tools;
      unsigned long mpn;
  
   unsigned long mpe ;
   unsigned long mpd ;
   unsigned long *n ;
   unsigned long *e ;
   unsigned long *d ;
   
  
  RSA();

  /* Performs RSA encryption.
     
     Uses internally stored public key for ecnryption.

     Parameters:
     plainText: the text to be encrypted.

     Return:
     RSA encryption of plainText.

     Note:
     This function has the same name as a previous one. That is not a
     problem. C++ can resolve which function you mean by looking at
     the number of argments and their types. This is refered to as
     'function overloading'.
  */
  std::string encrypt(std::string plainText);

  /* Performs RSA decryption.
     
     Uses internally stored private key for ecnryption.

     Parameters:
     cipherText: the text to be decrypted.

     Return:
     RSA decryption of cipherText.

     Note:
     This function has the same name as a previous one. That is not a
     problem. C++ can resolve which function you mean by looking at
     the number of argments and their types. This is refered to as
     'function
     overloading'.
  */
  std::string decrypt(std::string cipherText);
};

#endif 
