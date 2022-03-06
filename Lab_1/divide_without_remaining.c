#include "divide_without_remaining.h"


void print_binary(int number)
{
    for(int i = 0; i < 8; ++i)
    {
        printf("%d", number & 0x01);
        number >>= 0x01;
    }
    printf("\n");
}

int binary_size(int number)
{
    number = abs(number);
    int size = 0x00;
    while(number)
    {
        ++size;
        number >>= 0x01;
    }
    return size;
}

int divide_without_remaining(int divident, int divider)
{
    if (divider == 0x00)
    {
        printf("Error! Division by zero.\n");
        exit(1);
    }
    int shift = binary_size(divident) - binary_size(divider);
    if (shift < 0) return 0x00;
    int shifted_divider = divider << shift;
    int remaining = divident;
    int result = 0x00;
    printf("Tact 0\n");
    print_binary(remaining);
    print_binary(shifted_divider);
    remaining -= shifted_divider;
    if (remaining < 0x00) result |= 0x00;
    else result |= 0x01;
    print_binary(remaining);
    printf("result: ");
    print_binary(result);
    for(int i = 0x00; i < shift; ++i)
    {
        printf("Tact %d\n", i+1);
        print_binary(remaining);
        print_binary(shifted_divider);
        remaining <<= 0x01;
        result <<= 0x01;
        if (remaining < 0) remaining += shifted_divider;
        else remaining -= shifted_divider;
        if (remaining < 0x00) result |= 0x00;
        else result |= 0x01;
        print_binary(remaining);
        printf("result: ");
        print_binary(result);
    }
    return result;
}
