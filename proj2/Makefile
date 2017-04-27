all: kruskal

kruskal: kruskal.o
	gcc -g -Wall -pedantic -o kruskal kruskal.o

kruskal.o: kruskal.c
	gcc -g -Wall -pedantic -c kruskal.c

clean:
	rm -f *.o kruskal
