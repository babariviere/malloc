/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_hlp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:10:04 by briviere          #+#    #+#             */
/*   Updated: 2018/02/07 11:07:25 by briviere         ###   ########.fr       */
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
	size_t	current;
	t_block	*block;

	left = 0;
	current = 0;
	block = page->start;
	while (block)
	{
		// TODO: add sizeof t_block
		if (block->free)
			current += block->len;
		else if (current > left)
		{
			left = current;
			current = 0;
		}
		else
			current = 0;
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

t_block			*page_request_space(t_page *ref, size_t len)
{
	size_t		left;
	t_block		*start;
	t_block		*current;

	left = 0;
	start = 0;
	current = ref->start;
	while (current)
	{
		if (current->free)
		{
			if (start == 0)
				start = current;
			// TODO: add size of block
			left += current->len;
		}
		else if (left >= len && start)
		{
			start->len = left;
			return (start);
		}
		else
		{
			start = 0;
			left = 0;
		}
		current = current->next;
	}
	return (0);
}
