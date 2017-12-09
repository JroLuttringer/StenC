#include <stdio.h>
#include <stdlib.h>

//struct to hold a pixel.
struct rgb
{
    int r;
    int g;
    int b;
};

//struct to hold the image and its info.
struct image
{
    char p;
    int format;
    int width;
    int height;
    int intensity;
    //struct rgb **rgb;
   struct rgb *pixels;
};

int main(int argc, char** argv){ 
	struct image m;
	int i,j;
	FILE *fp = fopen(argv[1], "r");
	char* var_name = argv[2];
	fscanf(fp, "%c%d\n", &m.p, &m.format);

    fscanf(fp, "%d %d\n", &m.width, &m.height);

    fscanf(fp, "%d\n", &m.intensity);

    printf("%c%d\n", m.p, m.format);
    printf("%d %d\n", m.width, m.height);
    printf("%d\n", m.intensity);
	//fseek(fp, 1, SEEK_CUR);
    //allocate array to hold the pixels
	m.pixels = (struct rgb*)malloc(m.width*m.height*sizeof(struct rgb));
	for(i=0;i<m.width * m.height ;i++){
	//	for(j=0; j<; j++){ 
			fread(&(m.pixels[(i*m.width*3)+j*3]), sizeof(struct rgb), 1, fp);
			printf("%d \n",m.pixels[(i*m.width*3)+j*3].b);

	//	}
	}

	printf("%s = ", var_name);
	printf("{");
	for(i=0;i<m.width * m.height;i++){
	/*	printf("{");    // foreach pixel
		for(j=0; j<m.height; j++){ 
			printf("%x",m.pixels[(i*m.width*3)+j*3].r);
			if(j+1 < m.height) printf(",");
		}
		printf("}");
		if(i+1 < m.width) printf(",");	 */
	}
	printf("};");

	fclose(fp);
}
