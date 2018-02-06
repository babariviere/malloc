/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:12:17 by briviere          #+#    #+#             */
/*   Updated: 2018/02/06 12:15:50 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_prv.h"

static pthread_mutex_t	*get_mutex(void)
{
	static pthread_mutex_t	mutex;

	return (&mutex);
}

void		lock_mutex(void)
{
	pthread_mutex_lock(get_mutex());
}

void		unlock_mutex(void)
{
	pthread_mutex_unlock(get_mutex());
}
