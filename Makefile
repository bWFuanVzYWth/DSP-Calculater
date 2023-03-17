test: dsp.h light_matrix.h light_matrix.c main.c
	gcc *.c -o test -Wall -Ofast -flto -pipe -march=native -mtune=native