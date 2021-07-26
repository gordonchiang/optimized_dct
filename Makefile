CFLAGS=-D${ALGO} -Wall -static -O3
DEPS=./src/main.c ./src/dct.c

ifdef S # generate assembly instead of executable
	OUTPUT=-S
endif
ifndef S
	OUTPUT=-o dct.exe
endif

ifeq (${ALGO}, NAIVE) # make <arm> ALGO=NAIVE
	DEPS+=./src/naive.c
endif

ifeq (${ALGO}, UNOPTIMIZED) # make <arm> ALGO=UNOPTIMIZED
	DEPS+=./src/unoptimized.c
endif

ifeq (${ALGO}, UNROLLED) # make <arm> ALGO=UNROLLED
	CFLAGS+=-DTRANSPOSE
	DEPS+=./src/unrolled.c
endif

ifeq (${ALGO}, NEON) # make arm ALGO=NEON
	CFLAGS+=-mfloat-abi=softfp -mfpu=neon
	DEPS+=./src/neon.c
endif

dct: ${DEPS}
	gcc $(CFLAGS) $^ $(OUTPUT)

arm: ${DEPS}
	arm-linux-gcc $(CFLAGS) $^ $(OUTPUT)

.PHONY clean:
clean:
	-rm -rf ./**/*.o ./*.exe
