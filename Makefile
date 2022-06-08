test: dsp.h light_matrix.h light_matrix.c main.c
	gcc main.c -o test -Wall light_matrix.c -Ofast -flto -pipe -march=native -mtune=native