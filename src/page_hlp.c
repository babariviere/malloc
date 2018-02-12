/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_hlp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:10:04 by briviere          #+#    #+#             */
/*   Updated: 2018/02/07 18:07:07 by briviere         ###   ########.fr       */
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
	size_t	total;
	size_t	left;
	size_t	current;
	t_block	*block;

	if (page == 0)
		return (0);
	total = page->len - sizeof(t_page);
	left = 0;
	current = 0;
	block = page->start;
	while (block)
	{
		if (block->free && current == 0)
			current += block->len;
		else if (block->free)
			current += block->len + sizeof(t_block);
		else if (current > left)
		{
			left = current;
			current = 0;
		}
		else
			current = 0;
		total -= sizeof(t_block) + block->len;
		block = block->next;
	}
	return (left + total);
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

// TODO: add block after each block creation to optimize space
// maybe use page_mem_left_total
t_block			*page_request_space(t_page *ref, size_t len)
{
	size_t		total;
	size_t		left;
	t_block		*start;
	t_block		*current;
	t_block		*last;

	if (ref == 0)
		return (0);
	total = ref->len - sizeof(t_page);
	left = 0;
	start = 0;
	last = 0;
	current = ref->start;
	while (current)
	{
		if (current->free)
		{
			if (start == 0)
				start = current;
			else
				left += sizeof(t_block);
			// TODO: add size of block
			left += current->len;
		}
		else if (left >= len && start)
		{
			start->len = len;
			if (current != start)
				start->next = current;
			else
				start->next = 0;
			start->free = 0;
			return (start);
		}
		else
		{
			start = 0;
			left = 0;
		}
		if ((current->len + sizeof(t_block)) >= total)
			total = 0;
		else
			total -= current->len + sizeof(t_block);
		last = current;
		current = current->next;
	}
	// TODO: should be called more often
	// TODO: if left != 0 take block start
	if ((left + total) >= len && last)
	{
		start = (t_block *)((char *)last + sizeof(t_block) + last->len);
		start->len = len;
		start->next = 0;
		start->free = 0;
		last->next = start;
		return (start);
	}
	return (0);
}
