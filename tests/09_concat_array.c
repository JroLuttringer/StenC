int main(){
	int array_a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int array_b[10] = { 11,12,13,14,15,16,17,18,19,42};
	int array_c[20];
	int i;
	for (i=0;  i<20; i++){
	       printi(i);
	       printf("\n");
	       if(i<10){
	       	array_c[i]=array_a[i];
	       }
 	       else {
       		array_c[i]=array_b[i-10];
		}
	}
	printf("Concaténation : \n");
	int j = 0;
	while( j<20 ){
	 printi(j);   
	 //printi(array_c[j]);
            printf("-");
	    j++;
	}
	printf("\n");
	return 0;
	}	
