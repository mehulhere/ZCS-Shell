all: date dir Q2

Q2: Q2.c
	gcc Q2.c -o Q2
	./Q2

date: date.c
	gcc date.c -o date

dir: dir.c
	gcc dir.c -o dir