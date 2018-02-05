/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:31:37 by briviere          #+#    #+#             */
/*   Updated: 2018/02/05 15:02:22 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include <stdio.h>

void	*malloc(size_t size)
{
	static t_page	*first_page;
	static size_t	page_size;
	t_zone			*tmp_zone;

	(void)size;
	if (page_size == 0)
		page_size = getpagesize();

	if (first_page == 0)
	{
		first_page = mmap(0, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
		first_page->len = page_size;
		first_page->next = 0;
		first_page->start = (t_zone *)(first_page + 1);
		tmp_zone = first_page->start;
		tmp_zone->len = size;
		tmp_zone->next = 0;
		tmp_zone->free = 0;
		printf("page size: %ld, zone size: %ld, alloc size: %ld\n", sizeof(t_page), sizeof(t_zone), page_mem_left(first_page));
		return (tmp_zone + 1);
	}
	return (first_page + 1);
}
