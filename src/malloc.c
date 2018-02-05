/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:31:37 by briviere          #+#    #+#             */
/*   Updated: 2018/02/05 15:41:23 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include <stdio.h>

void	*malloc(size_t size)
{
	static t_page	*first_page;
	static size_t	page_size;
	void			*res;

	res = 0;
	if (page_size == 0)
		page_size = getpagesize();
	if (first_page == 0)
	{
		first_page = page_create(size);
		res = first_page->start + 1;
	}
	else if (page_mem_left(first_page) >= size + sizeof(t_zone))
	{
		res = zone_create(first_page, size) + 1;
	}
	if (res == 0)
		return (0);
	printf("malloc  => page_addr: %p, zone_addr: %p, page_mem_left: %ld\n", first_page, res - sizeof(t_zone), page_mem_left(first_page));
	return (res);
}
