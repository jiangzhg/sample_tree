all:
	gcc -std=c99 -O3 main.c -o calc

clean:
	rm -f calc
