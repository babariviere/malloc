/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:57:31 by briviere          #+#    #+#             */
/*   Updated: 2018/02/06 15:09:06 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_prv.h"
#include "ft_io.h"
#include <stdio.h>

// TODO: pthread block
inline t_page	**get_first_page()
{
	static t_page	*page;

	return (&page);
}

t_page			*page_create(size_t size)
{
	t_page	*new_page;
	size_t	new_size;

	size = size + sizeof(t_page) + sizeof(t_block);
	new_size = size + page_size() - (size % page_size());
	if ((new_page = mmap(0, new_size, PROT_READ | PROT_WRITE,
						MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (MAP_FAILED);
	new_page->len = new_size;
	new_page->next = 0;
	new_page->start = 0;
	ft_putstr("new page: ");
	ft_putnbr(new_size);
	ft_putchar('\n');
	return (new_page);
}

void			page_append(t_page **ref, t_page *page)
{
	t_page	*curr;

	if (*ref == 0)
	{
		*ref = page;
		return ;
	}
	curr = *ref;
	while (curr->next)
		curr = curr->next;
	curr->next = page;
}

void			page_delete(t_page **ref, t_page *page)
{
	t_page	*start_ref;
	t_page	*prev;
	t_page	*next;

	if (*ref == page)
	{
		if (page->next)
			*ref = page->next;
		else
			*ref = 0;
		munmap(page, page->len);
		return ;
	}
	start_ref = *ref;
	next = page->next;
	prev = *ref;
	while (prev->next != page)
		prev = prev->next;
	munmap(page, page->len);
	prev->next = next;
	*ref = start_ref;
}
