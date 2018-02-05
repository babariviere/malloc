/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_hlp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:10:04 by briviere          #+#    #+#             */
/*   Updated: 2018/02/05 16:36:09 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_prv.h"

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
	t_block	*block;

	left = page->len - sizeof(t_page);
	block = page->start;
	while (block)
	{
		left -= sizeof(t_block);
		if (!block->free)
			left -= block->len;
		block = block->next;
	}
	return (left);
}

int				page_unused(const t_page *page)
{
	t_block	*block;

	block = page->start;
	while (block)
	{
		if (!block->free)
			return (0);
		block = block->next;
	}
	return (1);
}

t_page			*find_avail_page(t_page *ref, size_t len)
{
	while (ref)
	{
		if (page_mem_left(ref) >= (len + sizeof(t_block)))
			return (ref);
		ref = ref->next;
	}
	return (0);
}
