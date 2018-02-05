#include <stdio.h>
#include <ft_mem.h>

int		main(void)
{
	char	*addr;

	for (int i = 0; i < 10; i++)
	{
		addr = malloc(4000);
		addr = malloc(4097);
		//printf("program =>      addr: %p, malloced: %d\n", addr, 16 * (i + 1));
	}
	return (0);
}
