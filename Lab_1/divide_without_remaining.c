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
    remaining -= shifted_divider;
    if (remaining < 0x00) result |= 0x00;
    else result |= 0x01;
    for(int i = 0x00; i < shift; ++i)
    {
        remaining <<= 0x01;
        result <<= 0x01;
        if (remaining < 0) remaining += shifted_divider;
        else remaining -= shifted_divider;
        if (remaining < 0x00) result |= 0x00;
        else result |= 0x01;
    }
    return result;
}

int divide_without_remaining_visual(int divident, int divider)
{
    printf("  ");
    print_binary(divident);
    printf("/ ");
    print_binary(divider);
    printf("\n");
    if (divider == 0x00)
    {
        printf("Error! Division by zero.\n");
        exit(1);
    }
    int shift = binary_size(divident) - binary_size(divider);
    int tact = 0;
    if (shift < 0) return 0x00;
    int shifted_divider = divider;
    printf("Binary shift\n");
    for(int i = 0; i < shift; ++i)
    {
        printf("Tact %d\n", tact++);
        print_binary(shifted_divider);
        printf("\n");
        shifted_divider <<= 1;
    }
    printf("Tact %d\n", tact++);
    print_binary(shifted_divider);
    printf("\n");
    int remaining = divident;
    int result = 0x00;
    printf("Subtraction with shift\n");
    printf("Tact %d (divident - shifted_divider)\n  ", tact++);
    print_binary(remaining);
    printf("- ");
    print_binary(shifted_divider);
    printf("= ");
    remaining -= shifted_divider;
    print_binary(remaining);
    printf("\n");
    if (remaining < 0x00) result |= 0x00;
    else result |= 0x01;
    printf("Tact %d (add digit to result)\n", tact++);
    printf("result: ");
    print_binary(result);
    printf("\n");
    for(int i = 0x00; i < shift; ++i)
    {
        remaining <<= 0x01;
        printf("Tact %d (remaining shift)\n", tact++);
        print_binary(remaining);
        printf("\n");
        result <<= 0x01;
        printf("Tact %d (result shift)\nresult: ", tact++);
        print_binary(result);
        printf("\n");
        printf("Tact %d (remaining - shifted_divider)\n  ", tact++);
        print_binary(remaining);
        printf("- ");
        print_binary(shifted_divider);
        printf("= ");
        if (remaining < 0) remaining += shifted_divider;
        else remaining -= shifted_divider;
        print_binary(remaining);
        printf("\n");
        if (remaining < 0x00) result |= 0x00;
        else result |= 0x01;
        printf("Tact %d (add digit to result)\nresult: ", tact++);
        print_binary(result);
        printf("\n");
    }
    return result;
}
