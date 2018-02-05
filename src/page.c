/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:57:31 by briviere          #+#    #+#             */
/*   Updated: 2018/02/05 15:14:58 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

t_page			*page_create(size_t size)
{
	t_page	*new_page;
	size_t	needed_pages;
	size_t	new_size;

	needed_pages = (size + sizeof(t_page) + sizeof(t_zone)) / page_size() + 1;
	new_size = needed_pages * page_size();
	if ((new_page = mmap(0, new_size, PROT_READ | PROT_WRITE,
						MAP_PRIVATE | MAP_ANON, -1, 0)) == 0)
		return (0);
	new_page->len = new_size;
	new_page->next = 0;
	new_page->start = (t_zone *)(new_page + 1);
	new_page->start->len = size;
	new_page->start->next = 0;
	new_page->start->free = 0;
	return (new_page);
}

inline size_t	page_size()
{
	static size_t	size;

	if (size == 0)
		size = getpagesize();
	return (size);
}

size_t			page_mem_left(t_page *page)
{
	size_t	left;
	t_zone	*zone;

	left = page->len - sizeof(t_page);
	zone = page->start;
	while (zone)
	{
		left -= sizeof(t_zone);
		if (!zone->free)
			left -= zone->len;
		zone = zone->next;
	}
	return (left);
}

int				page_unused(const t_page *page)
{
	t_zone	*zone;

	zone = page->start;
	while (zone)
	{
		if (!zone->free)
			return (0);
		zone = zone->next;
	}
	return (1);
}
