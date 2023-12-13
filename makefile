all: Q2 date dir ls run_script

Q2: Q2.c
	gcc Q2.c -g -o Q2
	./Q2 

date: date.c
	gcc date.c -g -o date

dir: dir.c
	gcc dir.c -g -o dir

ls: ls.c
	gcc ls.c -g -o ls

.PHONY: run_script

run_script:
	python3 Video-to-Text/videoToTextColor.py Video-to-Text/1213.mp4

clean:
	rm -f Q2 date dir ls
