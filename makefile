All: Q1.o Q2.o Q3.o Q4.o

Q1: Q1.o
	gcc Q1.o -o Q1
	./Q1

Q2: Q2.o
	gcc Q2.o -o Q2
	./Q2

Q3: Q3.o
	gcc Q3.o -o Q3
	./Q3

Q4: Q3.o
	gcc Q4.o -o Q4
	./Q4

Q5: Q5.o
	gcc Q5.o -o Q5
	./Q5

Q1.o: Q1.c
	gcc Q1.c -o Q1.o

Q2.o: Q2.c
	gcc Q2.c -o Q2.o

Q3.o: Q3.c
	gcc Q3.c -o Q3.o

Q4.o: Q4.c
	gcc Q4.c -o Q4.o

Q5.o: Q5.c
	gcc Q5.c -o Q4.o

clear:
	rm *.o
	rm Q1 Q2 Q3 Q4 Q5