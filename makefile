All: Q1.o Q2.o Q3.o Q4.o

Q1: Q1.o Q1Tree.o
	gcc Q1.o Q1Tree.o -o Q1
	./Q1

Q2: Q2.o Q2Tree.o
	gcc Q2.o Q2Tree.o -o Q2
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

Q1.o: Q1.c Q1Tree.h
	gcc -c Q1.c

Q1Tree.o: Q1Tree.c Q1Tree.h
	gcc -c Q1Tree.c

Q2.o: Q2.c  Q2Tree.h
	gcc -c Q2.c

Q2Tree.o: Q2Tree.c Q2Tree.h
		gcc -c Q2Tree.c

Q3.o: Q3.c
	gcc -c Q3.c

Q4.o: Q4.c
	gcc -c Q4.c

Q5.o: Q5.c
	gcc -c Q5.c

clear:
	rm *.o
	rm Q1 Q2 Q3 Q4 Q5
