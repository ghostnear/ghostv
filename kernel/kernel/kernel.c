#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void)
{
	tty_init();
	puts("Hello World!");
}