/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 15:16:12 by briviere          #+#    #+#             */
/*   Updated: 2018/02/07 18:07:02 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_prv.h"

t_block	*block_create(t_page *dest, size_t size)
{
	t_block	*block;
	t_block	*prev_block;

	block = dest->start;
	if (block == 0)
	{
		dest->start = PAGE_DATA(dest);
		dest->start->len = size;
		dest->start->next = 0;
		dest->start->free = 0;
		return (dest->start);
	}
	while (block->next)
		block = block->next;
	prev_block = block;
	block = (t_block *)((char *)block + block->len + sizeof(t_block));
	prev_block->next = block;
	block->len = size;
	block->free = 0;
	block->next = 0;
	return (block);
}

// TODO:
//void	block_delete(t_page **ref, t_block *blk)
//{
//	
//}

// FIXME: unable to find page in certain condition
t_page	*get_block_page(const t_page *ref, const t_block *blk)
{
	t_page	*page;
	char	*tmp;

	page = (t_page *)ref;
	while (page)
	{
		tmp = (char *)page;
		if ((void *)tmp > (void *)blk)
		{
			page = page->next;
			continue ;
		}
		if ((void *)(tmp + page->len) > (void *)blk)
			return (page);
		page = page->next;
	}
	return (0);
}
