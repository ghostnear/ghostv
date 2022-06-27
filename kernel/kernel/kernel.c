#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void)
{
	tty_init();
	if(printf("%d a %d\n", 100, 200) == -1) return;
	printf("b %d c\n", 200);
}