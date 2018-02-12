#include "ft_mem.h"
#include <unistd.h>

int		main(void)
{
	int i;
	char *addr;

	i = 0;
	(void)write(1, "hello\n", 6);
	while (i < 10)
	{
		addr = malloc(1024);
		addr[0] = '0';
		addr[1] = '\n';
		if (addr[0] != '0')
			return (1);
		//printf("%p\n", addr);
		write(1, addr, 2);
		i++;
	}
	show_alloc_mem();
	return (0);
}
