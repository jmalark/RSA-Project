#Makefile

OPTS = -g -Wall -Werror

all: encrypt decrypt keygen factorial

encrypt: encrypt.cc numberTheory.h ReallyLongInt.o	
	g++ ${OPTS} -o encrypt encrypt.cc ReallyLongInt.o

decrypt: decrypt.cc numberTheory.h ReallyLongInt.o
	g++ ${OPTS} -o decrypt decrypt.cc ReallyLongInt.o

keygen: keygen.cc numberTheory.h ReallyLongInt.o
	g++ ${OPTS} -o keygen keygen.cc ReallyLongInt.o

ReallyLongInt.o: ReallyLongInt.cc ReallyLongInt.h
	g++ ${OPTS} -c ReallyLongInt.cc

factorial: factorial.cc ReallyLongInt.o
	g++ ${OPTS} -o factorial factorial.cc ReallyLongInt.o

clean: 
	rm *.o
	rm encrypt
	rm decrypt
	rm keygen
	rm factorial

cleanemacs:
	rm *~

