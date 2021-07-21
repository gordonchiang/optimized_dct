main: ./src/main.c ./src/unoptimized.c ./src/naive.c
	gcc -Wall -lm ./src/main.c ./src/unoptimized.c ./src/naive.c -o main.exe

arm: ./src/main.c ./src/unoptimized.c
	arm-linux-gcc -static ./src/main.c ./src/unoptimized.c -o main.exe

arm-neon: ./src/main.c ./src/neon.c
	arm-linux-gcc -Wall -mfloat-abi=softfp -mfpu=neon -static ./src/main.c ./src/neon.c -o main.exe

.PHONY clean:
clean:
	-rm -rf ./**/*.o ./*.exe
