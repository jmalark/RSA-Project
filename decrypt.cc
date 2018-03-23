//
//  decrypt.cc



#include <iostream>
#include <fstream>
#include "numberTheory.h"
#include <cstring>
#include "ReallyLongInt.h"

using namespace std;



//takes private key file, encrypted file, output file as command line arguments
int main(int argc, char** argv)

{
    //private key
    ifstream fin(argv[1]);
    
    //reads the first 2 int's from the the input file into d and n
    string d;
    string n;
    fin >> d;
    fin >> n;
    
    //encrypted file and decrypted file
    ifstream inputF(argv[2]);
    ofstream outputF(argv[3]);
    
    string num;
    //ReallyLongInt num;
    //unsigned long long num;
    inputF >> num;
    
    //will loop while there are still int's to input
    while(!inputF.eof())
    {
        //writes a char to the output file after modPower and the private key are used to decrypt the int
      ReallyLongInt storeMod(modPower(ReallyLongInt(num), ReallyLongInt(d), ReallyLongInt(n)));
      long long lLongvers = storeMod.toLongLong();
      outputF << char(lLongvers);
        
        //updates num
        inputF >> num;
    }
}
