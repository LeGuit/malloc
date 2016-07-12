#include <stdio.h>
#include <unistd.h>

#define ALIGN4(size)			(((size) + 0b11) & ~0b11)

#define DEBUG_ALIGN(size)	printf("%d -> %d\n", size, ALIGN4(size))


int main(void)
{
	int i;

	DEBUG_ALIGN(0);
	DEBUG_ALIGN(1);
	DEBUG_ALIGN(2);
	DEBUG_ALIGN(3);
	DEBUG_ALIGN(4);
	DEBUG_ALIGN(5);
	i = getpagesize();
	printf("|%d|", i);
	return (0);
}

/*
** getpagesize = 4096 => 2^12
** tiny = 2MB => 2097152 => 2^21 512 * pagesize
** small = 16MB => 16777216 => 2^24 4096 * pagesize
*/
