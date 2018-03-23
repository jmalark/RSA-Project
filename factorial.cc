//factorial.cc

#include "ReallyLongInt.h"
#include <iostream>


//takes x as a command line argument
//finds and prints x!
int main(int argc, char** argv)
{
  ReallyLongInt x(argv[1]);
  ReallyLongInt ans(1);
  ReallyLongInt idx(1);
  

  
  while (idx <= x) 
    { 
      ans *= idx;
      ++idx;
      
    }
 
  cout <<ans<< endl;

}
