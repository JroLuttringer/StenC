int main(){
int A; int B; int C;
A = 834389; B = 944353;
  while(1==1)
  {
    if (A<B)
    {
      C=A; A=B; B=C;
    }
    if (A==B)
    {
      printf("La valeur du PGCD est :");
      printi(A);
      printf("\n");
      return 0;
    }
    A=A-B;
  }
  return 0;
}