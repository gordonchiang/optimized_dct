CC=gcc
CFLAGS=-c -Wall -g

main: ./src/main.c ./src/unoptimized_algo.c ./src/naive.c
	$(CC) -Wall -lm ./src/main.c ./src/unoptimized_algo.c ./src/naive.c -o main.exe

.PHONY clean:
clean:
	-rm -rf ./**/*.o ./*.exe
