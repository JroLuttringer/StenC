int main(){
	int x = 1;
	if( 1==1 || (x/0) == -1){
		printf("In if (short circuited division by zero) \n");
	}
	return 0;
}
