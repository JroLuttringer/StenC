int main()
{
    int i;
    int n=15;
    int t1 = 0;
    int t2 = 1;
    int nextTerm;
    printf("Fibonacci Series: \n");
    for (i = 1; i <= n; i++)
    {
        printi(t1);
        printf(", ");
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }
    printf("\n");
    return 0;
}