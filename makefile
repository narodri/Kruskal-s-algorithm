all : Kruskal

Kruskal.o : Kruskal.c
	gcc -c -o Kruskal.o Kruskal.c

Kruskal : Kruskal.o
	gcc -o Kruskal Kruskal.o

clean:
	rm Kruskal.o Kruskal Kruskal_result.txt
	
