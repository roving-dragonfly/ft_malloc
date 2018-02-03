#include <stdio.h>
#include <unistd.h>
#include "malloc.h"

int main()
{
	printf("%u\n", getpagesize());
	ft_malloc(15);
}
