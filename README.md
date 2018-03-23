# RSA-Project
Project from Computer Science III where I implimented the RSA encryption algorithm in C++


Jessica Malark
CPS 222 Project 1

Files submitted:
ReallyLongInt.cc
ReallyLongInt.h
factorial.cc
numberTheory.h
keygen.cc
encrypt.cc
decrypt.cc
Makefile
readme.txt
Homework Cover Sheet.pdf

This project contains several runnable files and the other files they depend on. The command ‘make all’ with compile the project or the files can be compiled individually according to the instructions below. 

---factorial---
To compile: make factorial
To run: ./factorial <number>
Description: factorial will compute and print out the factorial of the number provided as a command line argument.

Known issues:
-anything over five digits takes awhile to compute. 4 digits numbers are fine. Smaller 5 digits are fine, but the time it would take to compute numbers higher than that is unknown



---keygen---
To compile: make keygen
To run: ./keygen <prime> <prime> <publicKeyFile.txt> <privateKeyFile.txt>
Description:
This program will generate two keys (one public and one private) which can be used by later programs to encrypt and decrypt files (respectively). The product of the two prime numbers given as command line arguments must exceed 256. (Aka <prime> * <prime> must be > 256). The keys will be written to the appropriate files.

No known issues.


--encrypt--
To compile: make encrypt
To run: ./encrypt <publicKeyFile.txt> <toEncrypt.txt> <encrypted.txt>
Description: Will encrypt the message. The encrypted message is written into the file provided as the third command line argument

No known issues.


--decrypt--
To compile: make decrypt
To run: ./decrypt <privateKeyFile.txt> <encrypted.txt> <decrypted.txt>
Description: Will decrypt the message. 

Known issues:
When huge keys (very large primes were given to keygen) are used, long messages take a long time to decrypt. A hundred digit prime with a fifty digit prime was fine for decrypting the message “Hi.”.  However, that would not be the case if the message was longer. Decrypting long messages with huge keys would take an undesirable amount of time.
