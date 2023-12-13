all: Q2 date dir ls run_script

Q2: Q2.c
	gcc Q2.c -o Q2
	./Q2 

date: date.c
	gcc date.c -o date

dir: dir.c
	gcc dir.c -o dir

ls: ls.c
	gcc ls.c -o ls

.PHONY: run_script

run_script:
	python3 Video-to-Text/videoToTextColor.py Video-to-Text/1213.mp4

clean:
	rm -f Q2 date dir ls
