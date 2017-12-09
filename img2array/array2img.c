#include <stdlib.h>
#include <stdio.h>
int main(int argc, char** argv){
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	FILE *in = fopen(argv[3], "r");
	FILE *f = fopen("out.ppm", "wb");
	int array_in[width][height];
	int i,j;
 	for (i = 0; i < width; i++){
		for(j=0; j < height;j++){
       			fscanf(in, "%d,", &array_in[i][j] );
		}
    	}

	fprintf(f, "P6\n%i %i 255\n", width, height);
	for (int x=0; x<width; x++) {
	    for (int y=0; y<height; y++) {
		fputc(array_in[x][y], f);   // 0 .. 255
		fputc(array_in[x][y], f); // 0 .. 255
		fputc(array_in[x][y], f);  // 0 .. 255
	    }
	}
	fclose(f);
	return 0;
}
