/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:32:05 by briviere          #+#    #+#             */
/*   Updated: 2018/02/05 15:17:06 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <string.h>
# include <sys/mman.h>
# include <unistd.h>

typedef struct	s_zone {
	size_t			len;
	int				free;
	struct s_zone	*next;
}				t_zone;

typedef struct	s_page {
	size_t			len;
	struct s_zone	*start;
	struct s_page	*next;
}				t_page;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

/** FUTURE PROTOTYES **/
t_page	*page_create(size_t size);
size_t	page_size();
size_t	page_mem_left(t_page *page);
int		page_unused(const t_page *page);

t_zone	*zone_create(t_page *dest, size_t size);

#endif
