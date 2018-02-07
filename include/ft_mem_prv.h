/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_prv.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 15:58:16 by briviere          #+#    #+#             */
/*   Updated: 2018/02/07 11:06:10 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEM_PRV_H
# define FT_MEM_PRV_H

# include <pthread.h>
# include <string.h>
# include <sys/mman.h>
# include <unistd.h>

# define BLOCK_SIZE (sizeof(t_block))
# define BLOCK_DATA(x) ((void *)((char *)x + BLOCK_SIZE + 1))

# define PAGE_SIZE (sizeof(t_page))
# define PAGE_DATA(x) ((void *)((char *)x + PAGE_SIZE + 1))

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

t_page			**get_first_page();

/** FUTURE PROTOTYES **/
t_page			*page_create(size_t size);
void			page_append(t_page **ref, t_page *page);
void			page_delete(t_page **ref, t_page *page);
size_t			page_size();
size_t			page_mem_left(t_page *page);
int				page_unused(const t_page *page);
t_page			*find_avail_page(t_page *ref, size_t len);
t_block			*page_request_space(t_page *ref, size_t len);

t_block			*block_create(t_page *dest, size_t size);
t_page			*get_block_page(const t_page *ref, const t_block *blk);

void			lock_mutex(void);
void			unlock_mutex(void);

#endif
