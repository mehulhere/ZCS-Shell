all:  date dir ls shell

shell: shell.c
	gcc shell.c -o shell
	./shell 

date: date.c
	gcc date.c -o date

dir: dir.c
	gcc dir.c -o dir

ls: ls.c
	gcc ls.c -o ls

clean:
	rm -f Q2 date dir ls
