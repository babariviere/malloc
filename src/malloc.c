/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:31:37 by briviere          #+#    #+#             */
/*   Updated: 2018/02/09 19:54:12 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_prv.h"
#include "ft_io.h"
#include <stdio.h>

void	*malloc_core(size_t size)
{
	t_page	**first_page;
	t_page	*page;
	t_block	*res;

	res = 0;
	ft_putstr("malloc request: ");
	ft_putnbr(size);
	ft_putchar('\n');
	first_page = get_first_page();
	if (*first_page == 0)
	{
		*first_page = page_create(size);
		page = *first_page;
		res = block_create(page, size);
	}
	else
	{
		// TODO: fix when there is enough space but not in one block
		page = find_avail_page(*first_page, size);
		if (page)
			res = page_request_space(page, size);
		if (page == 0 || res == 0)
		{
			page = page_create(size);
			page_append(first_page, page);
			res = block_create(page, size);
		}
	}
	if (res == 0)
		return (0);
	//ft_putstr("page_addr: ");
	//ft_putaddr(*first_page);
	//ft_putstr(", block_addr: ");
	//ft_putaddr(res);
	//ft_putchar('\n');
	ft_putstr("malloced: ");
	ft_putaddr(BLOCK_DATA(res));
	ft_putchar('\n');
	return (BLOCK_DATA(res));
}

void	*malloc(size_t size)
{
	void	*res;

	lock_mutex();
	res = malloc_core(size);
	unlock_mutex();
	return (res);
}
