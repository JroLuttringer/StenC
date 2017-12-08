int main()
{
    int rows = 6;
    int coef = 1;
    int space; 
    int i; 
    int k;

    for(i=0; i<rows; i++)
    {
        for(space=1; space <= rows-i; space++){
            printf("  ");
        }

        for(k=0; k <= i; k++)
        {
            if (k==0 || i==0) {
                coef = 1;
            }
            else {
                coef = coef*(i-k+1)/k;
            }

            printi(coef);
            printf("   ");
        }
        printf("\n");
    }

    return 0;
}