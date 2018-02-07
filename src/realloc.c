/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:00:02 by briviere          #+#    #+#             */
/*   Updated: 2018/02/07 11:38:42 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_prv.h"
#include "ft_io.h"

void *realloc(void *ptr, size_t size)
{
	(void)ptr;
	(void)size;
	ft_putendl("realloc called but not implemented :(");
	return (0);
}
