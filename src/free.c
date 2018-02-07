/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:13:27 by briviere          #+#    #+#             */
/*   Updated: 2018/02/07 11:08:43 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_prv.h"
#include "ft_io.h"
#include <stdio.h>

void	free(void *ptr)
{
	t_page	**first_page;
	t_page	*page;
	t_block	*blk;

	ft_putstr("try freeing: ");
	ft_putaddr(ptr);
	ft_putchar('\n');
	if (ptr == 0)
		return ;
	lock_mutex();
	first_page = get_first_page();
	if (first_page == 0)
		return ;
	blk = (t_block *)ptr - 1;
	blk->free = 1;
	page = get_block_page(*first_page, blk);
	unlock_mutex();
	ft_putaddr(page);
	ft_putchar('\n');
	// TODO: 
	if (page == 0)
		return ;
	if (page_unused(page))
	{
		lock_mutex();
		ft_putendl("free unused page");
		page_delete(first_page, page);
		unlock_mutex();
	}
}
