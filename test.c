int main(){
	int tab[5][5];
	int i = 0;
	int i2 = 0;
	while (i < 5) {
		i2 = 0;
		while (i2 < 5) {
			tab[i][i2] = i*i2;
			i2++;
		}
		i++;
	}
	i = 0;
	for (i = 0 ; i < 25 ; i++) {
		printi(tab[i]);
		printf(" ");
	}
	tab[0][0]=tab[4][4];
	printf("\n");
	printi(tab[0][0]);
	printf("\n");
	return 0;
}