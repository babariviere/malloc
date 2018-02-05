/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_prv.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 15:58:16 by briviere          #+#    #+#             */
/*   Updated: 2018/02/05 16:38:58 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEM_PRV_H
# define FT_MEM_PRV_H

# include <string.h>
# include <sys/mman.h>
# include <unistd.h>

typedef struct	s_block {
	size_t			len;
	int				free;
	struct s_block	*next;
}				t_block;

typedef struct	s_page {
	size_t			len;
	struct s_block	*start;
	struct s_page	*next;
}				t_page;

/** FUTURE PROTOTYES **/
t_page			*page_create(size_t size);
void			page_append(t_page **ref, t_page *page);
size_t			page_size();
size_t			page_mem_left(t_page *page);
int				page_unused(const t_page *page);
t_page			*find_avail_page(t_page *ref, size_t len);

t_block			*block_create(t_page *dest, size_t size);
t_page			*get_block_page(const t_page *ref, const t_block *blk);

#endif