int main()
{
    int n1 = 18;
    int n2 = 0 ;
    int n3 = -5;
    if (n1>=n2)
    {
        if(n1>=n3) {
            printi(n1);
            printf(" is the largest number.\n");
            }
        else {
            printi(n3);
            printf(" is the largest number.\n");
            }
    }
    else
    {
        if(n2>=n3) {
            printi(n2);
            printf(" is the largest number.\n");
            }
        else {
            printi(n3);
            printf(" is the largest number.\n");
            }
    }
    
    return 0;
}