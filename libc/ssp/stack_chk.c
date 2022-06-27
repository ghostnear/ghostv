#include <stdint.h>
#include <stdlib.h>
 
// TODO: change these they are temporary like this
#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xdeadbeef
#else
#define STACK_CHK_GUARD 0xdeadbeefdeadbeef
#endif
 
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;
 
//__attribute__((noreturn))
void __stack_chk_fail(void)
{
#if __STDC_HOSTED__
	abort();
#elif __is_ghostv_kernel
	panic("Stack smashing detected");
#endif
}