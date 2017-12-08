int main () {

   /* an array with 5 rows and 2 columns*/
   int a[5][2] = { {0,0}, {1,2}, {2,4}, {3,6},{4,8}};
 // int a[2][2] = { {1,1},{1,1} };
   int i;
   int k;
 
   /* output each array element's value */
   for ( i = 0; i < 5; i++ ) {
      for ( k = 0; k < 2; k++ ) {
          printf("a[");printi(i);printf("][");printi(k);printf("] = ");printi(a[i][k]);printf("\n");
      }
   }
   
   return 0;
}