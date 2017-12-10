int main(){
  int a=11; // coeff du polynome
  int b=-12;
  int c=1;
  int discriminant = b*b - 4*a*c;
  int sqrt_d = discriminant;
  int y = 1;
  int e = 1;
  // racine carré discriminant
  while(sqrt_d - y > e)
  {
    sqrt_d = (sqrt_d + y)/2;
    y = discriminant/sqrt_d;
}
  printf("Discriminant : ");printi(discriminant);
  printf(" racine du discriminant : ");printi(sqrt_d); printf("\n");

  if( discriminant == 0){
    printf("Le discriminant est nul\n");
    printf("Solution :\n");
    printi(-b / (2*a));
    printf("\n");
  } else {
    if(discriminant>0) {
      printf("Discriminant positif\n");
      printf("Solutions :\n");
      int x1 = (-b + sqrt_d)/(2*a) ;
      int x2 = (-b - sqrt_d)/(2*a) ;
      printi(x1); printf(" and ");printi(x2);
      printf("\n");
    } else {
      printf("Discriminant négatif\n");
    }
  }

  return 0;
}