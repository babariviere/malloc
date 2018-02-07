#include "ft_mem.h"
int		main(void)
{
	int i;
	char *addr;

	i = 0;
	write(1, "hello\n", 6);
	while (i < 10)
	{
		addr = malloc(1024);
		addr[0] = 0;
		if (addr[0] != 0)
			return (1);
		//printf("%p\n", addr);
		i++;
	}
	return (0);
}
