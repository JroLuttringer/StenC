int main()
{
    int base = 12;
    int exponent = 6;

    int result = 1;

    while (exponent != 0)
    {
        result = result * base;
        exponent--;
    }

    printf("Answer = "); 
    printi(result);

    return 0;
}