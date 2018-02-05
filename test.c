#include <stdio.h>
#include <ft_mem.h>

int		main(void)
{
	char	*addr;
	char	*addrs[20];

	for (int i = 0; i < 20; i+=2)
	{
		addr = malloc(4000);
		addrs[i] = addr;
		addr = malloc(4097);
		addrs[i + 1] = addr;
		//printf("program =>      addr: %p, malloced: %d\n", addr, 16 * (i + 1));
	}
	// TODO: fix free which free only one page
	for (int i = 0; i < 20; i += 2)
	{
		free(addrs[i]);
	}
	return (0);
}
