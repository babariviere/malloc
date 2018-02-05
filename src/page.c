/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:57:31 by briviere          #+#    #+#             */
/*   Updated: 2018/02/05 15:01:19 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

size_t		page_mem_left(t_page *page)
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
