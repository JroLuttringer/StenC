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

/*    for(exponent=exponent; exponent != 0; exponent--){
      result = result * base;
    }*/
    printf("Answer = "); 
    printi(result);

    return 0;
}