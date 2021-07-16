CC=gcc
CFLAGS=-c -Wall -g

main: ./src/main.o ./src/unoptimized_algo.o ./src/naive.o
	$(CC) -Wall -lm ./src/main.o ./src/unoptimized_algo.o ./src/naive.o -o main.exe

.PHONY clean:
clean:
	-rm -rf ./**/*.o ./*.exe
