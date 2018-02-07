/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:29:15 by briviere          #+#    #+#             */
/*   Updated: 2018/02/07 17:35:59 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_mem_prv.h"

void	show_alloc_mem(void)
{
	t_page		*curr_page;
	t_block		*curr_block;

	curr_page = *get_first_page();
	while (curr_page)
	{
		ft_putsize(curr_page->len);
		ft_putstr(": ");
		ft_putaddr(curr_page);
		ft_putchar('\n');
		curr_block = curr_page->start;
		while (curr_block)
		{
			if (!curr_block->free)
			{
				ft_putstr("  ");
				ft_putaddr(curr_block);
				ft_putstr(" - ");
				ft_putaddr((char *)curr_block + sizeof(t_block) + curr_block->len);
				ft_putstr(" : ");
				ft_putsize(curr_block->len);
				ft_putendl(" octets");
			}
			curr_block = curr_block->next;
		}
		curr_page = curr_page->next;
	}
}
