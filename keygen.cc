//keygen.cc

#include <iostream>
#include "numberTheory.h"
#include <fstream>
#include <cstdlib>
#include "ReallyLongInt.h"

using namespace std;

//takes 2 prime numbers, public key filename, private key filename 
int main(int argc, char** argv)
//will generate a matched pair of public and private keys

{
  /*initializes variables p and q to hold the prime numbers provided. Uses atol to convert the string stored from the command line into a long int
   */
  ReallyLongInt p(argv[1]);
  ReallyLongInt q(argv[2]);

  /*if either of the primes given isn't prime it prints a msg to the screen and stops the function 
   */
  if(p > 100000 || q > 100000)
    {
      cout<<"Primality is not being verified" << endl;
    }
  else if (!isPrime(p)|| !isPrime(q))
    {  cout << "Error: you entered a number that wasn't prime"<< endl;
      return 1;
    }

  //makes accessable output files with the provided file names
  ofstream privKeyF(argv[4]);
  ofstream pubKeyF(argv[3]);

  
  ReallyLongInt n(p * q);
  ReallyLongInt t((p -1)*(q -1));
  

  ReallyLongInt e;
  ReallyLongInt x;
  ReallyLongInt y;
  
  ReallyLongInt* px = &x;
  ReallyLongInt* py = &y;
  
  /*if extendedEuclid finds a relatively prime number for t, e gets set to eTest's value and eTest goes to 0 so that even when it hits the updater it doesn't satisfy the while loop condition */
  ReallyLongInt eTest(2);
  while(eTest > 1 && eTest < t)
    {if (extendedEuclid(eTest, t, px, py) == 1)
	{
	 e = eTest;
	 eTest = 0;
     	}
      eTest++;
    }
  /*after the while loop there could be an issue if x (updated through extended Euclid) is negative. If it is it changes x according to what project pdf said */
      if (x < 0)
	{x = x + t;
	}
      //writes e space n as the public key and x space n as the private key
      pubKeyF << e << " " << n;
      privKeyF << x << " " << n;
}

