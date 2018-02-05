/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 15:16:12 by briviere          #+#    #+#             */
/*   Updated: 2018/02/05 15:20:23 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

t_zone	*zone_create(t_page *dest, size_t size)
{
	t_zone	*zone;
	t_zone	*prev_zone;
	char	*ptr;

	zone = dest->start;
	while (zone->next)
		zone = zone->next;
	prev_zone = zone;
	ptr = (char *)zone;
	zone = (t_zone *)(ptr + zone->len);
	zone += 1;
	prev_zone->next = zone;
	zone->len = size;
	zone->free = 0;
	zone->next = 0;
	return (zone);
}
