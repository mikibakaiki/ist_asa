all: asaproj

asaproj: asaproj.o
	gcc -g -Wall -pedantic -o asaproj asaproj.o

asaproj.o: asaproj.c
	gcc -g -Wall -pedantic -c asaproj.c

clean:
	rm -f *.o asaproj
