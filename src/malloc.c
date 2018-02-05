/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:31:37 by briviere          #+#    #+#             */
/*   Updated: 2018/02/05 17:21:45 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_prv.h"
#include <stdio.h>

void	*malloc(size_t size)
{
	t_page	**first_page;
	t_page	*page;
	void	*res;

	res = 0;
	first_page = get_first_page();
	if (*first_page == 0)
	{
		*first_page = page_create(size);
		page = *first_page;
	}
	else
	{
		page = find_avail_page(*first_page, size);
		if (page == 0)
		{
			page = page_create(size);
			page_append(first_page, page);
		}
	}
	res = block_create(page, size) + 1;
	if (res == 0)
		return (0);
	printf("malloc  => page_addr: %p, block_addr: %p, page_mem_left: %ld\n", *first_page, res - sizeof(t_block), page_mem_left(*first_page));
	return (res);
}
