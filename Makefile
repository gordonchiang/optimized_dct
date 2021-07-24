CFLAGS=-D${ALGO} -Wall -static
DEPS=./src/main.c

ifeq (${ALGO}, NAIVE) # make <arm> ALGO=NAIVE
	DEPS+=./src/naive.c
endif

ifeq (${ALGO}, UNOPTIMIZED) # make <arm> ALGO=UNOPTIMIZED
	DEPS+=./src/unoptimized.c
endif

ifeq (${ALGO}, UNROLLED) # make <arm> ALGO=UNROLLED
	DEPS+=./src/unrolled.c
endif

ifeq (${ALGO}, NEON) # make arm ALGO=NEON
	CFLAGS+=-mfloat-abi=softfp -mfpu=neon
	DEPS+=./src/neon.c
endif

dct: ${DEPS}
	gcc $(CFLAGS) $^ -o dct.exe

arm: ${DEPS}
	arm-linux-gcc $(CFLAGS) $^ -o dct.exe

.PHONY clean:
clean:
	-rm -rf ./**/*.o ./*.exe
