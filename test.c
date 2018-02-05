#include <stdio.h>
#include <ft_mem.h>

int		main(void)
{
	size_t	size;
	char	*addr;

	addr = malloc(11);
	for (int i = 0; i < 10; i++)
		addr[i] = '0';
	addr[10] = 0;
	printf("%s\n", addr);
	for (int i = 0; i < 10; i++)
		printf("addr=%p\n", malloc(11));
	return (0);
}
