#include <stdlib.h>
#include <math.h>

// !! This assumes str is big enough to be able to store all the digits of n.
// TODO: make this work for bases that are bigger than 10
char* itoa(int n, char* str, int base)
{
    // Get the digit count for n
    int n_abs = abs(n), n_c = 0;
    do {
        n_abs /= base, n_c++;
    }
    while(n_abs);

    // Copy so we don't break str
    char* o_str = str;

    // For negative numbers, save - then print the positive value
    if(n < 0)
    {
        (str++)[0] = '-';

        // Invert
        n = -n;
    }

    // Reuse n_abs as the counter
    n_abs = 1;
    while(n)
    {
        // Save the digit to the string
        str[n_c - n_abs] = ('0' + n % base);

        // Advance
        n_abs++;
        n /= base;
    }
    str[n_c + 1] = '\0';

    // Restore the state
    str = o_str;
    return str;
}