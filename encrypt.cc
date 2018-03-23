//encrypt.cc

#include "numberTheory.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include "ReallyLongInt.h"

using namespace std;

//encrypts plaintext
//takes public key file, file to encrypt, encrypted file name
int main(int argc, char** argv)

{
    //makes input file accessable
    ifstream fin(argv[1]);
    
    
    string e;
    string n;
    fin >> e;
    fin >> n;
    
    
    
    ifstream inputFile(argv[2]);
    ofstream outputFile(argv[3]);
    
    //declares c as a char so the inputFile can read a char into it for its value
    char c;
    
    //while there are still char's in the file also update c
    while(inputFile.get(c))
    {
        //write modPower used on the int version of c to outputFile and an endline
      
      //ReallyLongInt modRes = modPower(ReallyLongInt(int(c)), ReallyLongInt(e), ReallyLongInt(n));
      outputFile << modPower(ReallyLongInt(int(c)), ReallyLongInt(e), ReallyLongInt(n)) << endl;

      //outputFile << modRes <<endl;
    }
    
}

