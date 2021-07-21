main: ./src/main.c ./src/unoptimized.c ./src/naive.c ./src/neon.c
	gcc -D$(ALGO) -Wall -lm ./src/main.c ./src/unoptimized.c ./src/naive.c ./src/neon.c -o dct.exe

arm: ./src/main.c ./src/unoptimized.c ./src/neon.c
	arm-linux-gcc -D$(ALGO) -static ./src/main.c ./src/unoptimized.c ./src/neon.c -o dct.exe

arm-neon: ./src/main.c ./src/neon.c
	arm-linux-gcc -D$(ALGO) -Wall -mfloat-abi=softfp -mfpu=neon -static ./src/main.c ./src/neon.c -o dct.exe

.PHONY clean:
clean:
	-rm -rf ./**/*.o ./*.exe
