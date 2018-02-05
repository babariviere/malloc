/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:13:27 by briviere          #+#    #+#             */
/*   Updated: 2018/02/05 17:26:49 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_prv.h"
#include <stdio.h>

void	free(void *ptr)
{
	t_page	**first_page;
	t_page	*page;
	t_block	*blk;

	first_page = get_first_page();
	if (first_page == 0)
		return ;
	blk = ptr - sizeof(t_block);
	page = get_block_page(*first_page, blk);
	blk->free = 1;
	if (page_unused(page))
	{
		printf("page unused: %p\n", page);
		page_delete(first_page, page);
	}
}
