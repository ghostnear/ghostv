#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Manually prints the data string to the output
static bool print(const char* data, size_t length)
{
	// Make data unsigned
	const uint8_t* bytes = (const uint8_t*) data;

	// Go trough the data and write everything
	for(size_t i = 0; i < length; i++)
		if(putchar(bytes[i]) == EOF)
			return false;
	return true;
}

// Just like printf but from va_list
int vprintf(const char* format, va_list list)
{
	// Number of bytes allowed to be printed
	int written = 0;

	// Loop trough the array
	while(format[0] != '\0')
	{
		// The maximum storage we have
		size_t maxrem = INT_MAX - written;

		if(format[0] != '%' || format[1] == '%')
		{
			// Advance if we are at a %
			if(format[0] == '%')
				format++;
			
			// Start from the second char and go to the next %
			size_t amount = 1;
			while(format[amount] && format[amount] != '%')
				amount++;
			
			// If there's too much data
			if(maxrem < amount)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}

			// Print out the data
			if(!print(format, amount))
				return -1;

			// Advance and update the bytes
			format += amount;
			written += amount;
			continue;
		}

		// Get the position where the % is at
		const char* format_begun_at = format++;

		// Check format type

		// Char
		if(format[0] == 'c')
		{
			// Skip the c
			format++;

			// Get the argument (char promotes to int, convert it back)
			char c = (char) va_arg(list, int);

			// If there is no available space
			if(!maxrem)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}

			// Print the char to the screen
			if(!print(&c, sizeof(c)))
				return -1;
			
			// Update count
			written++;
		}
		// String
		else if(format[0] == 's')
		{
			// Skip the s
			format++;

			// Get data about the string
			const char* str = va_arg(list, const char*);
			size_t len = strlen(str);

			// If there's no space left
			if(maxrem < len)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}

			// Print the string
			if (!print(str, len))
				return -1;

			// Update count
			written += len;
		}
		// Decimal (int)
		else if(format[0] == 'd' || format[0] == 'i')
		{
			// Skip the d / i
			format++;

			// Get the argument
			int n = va_arg(list, int);
			size_t n_abs = abs(n), n_c = 0;
			n_c += (n < 0);
			do {     n_abs /= 10, n_c++;	}
			while(n_abs);
			
			// If there's no space left
			if(maxrem < n_c)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}

			// Allocate buffer (assume for now it can't get bigger until the heap becomes a thing)
			// TODO: check this out after you got the heap working
			char res[64];
			if(!itoa(n, res, 10))
				return -1;

			// Print to the screen
			if(!print(res, n_c))
				return -1;
			
			// Update count
			written += n_c;
		}
		// Unknown format
		else
		{
			// Go back
			format = format_begun_at;

			// Get the length of the rest of the string
			size_t len = strlen(format);

			// If there's no space left
			if(maxrem < len)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}

			// Print
			if(!print(format, len))
				return -1;

			// Update position and count
			written += len;
			format += len;
		}
	}
	return written;
}

// https://cplusplus.com/reference/cstdio/printf/

int printf(const char* restrict format, ...)
{
	// Variable argument mode
	va_list parameters;
	va_start(parameters, format);

	int written = vprintf(format, parameters);

	// Return the result and end the variable argument mode
	va_end(parameters);
	return written;
}
