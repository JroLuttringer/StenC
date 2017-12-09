int main () {


	int tab[3][3] = { {1,2,3}, {4,5,6}, {7,8,9} };
	stencil test{1,2} = { {1,0,0}, {1,0,0}, {1,0,0} };
	int x = (tab[1][1] $ test);
	printi(x);
	printf("\n");
	return 0;
}