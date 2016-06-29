#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int i;

	i = getpagesize();
	printf("|%d|", i);
	return (0);
}

/*
** getpagesize = 4096 => 2^12
** tiny = 2MB => 2097152 => 2^21 512 * pagesize
** small = 16MB => 16777216 => 2^24 4096 * pagesize
*/
