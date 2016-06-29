/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 11:47:56 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/06/29 18:40:31 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"

/*
** ========================================================================== **
** ALIGN4 =>		check if align 4 or 8
** 					this define align to the next 4 multiple
** CHUNK_SIZE =>	size of the header of a chunk
*/
//# define	ALIGN4(x)	(((((x) - 1) >> 2) << 2) + 4)
# define	CHUNK_SIZE	sizeof(t_chunk)
# define	META_SIZE	sizeof(t_block)
# define	PAGE_SIZE	(4096)
# define	TINY_SIZE	(521 * PAGE_SIZE)
# define	SMALL_SIZE	(4096 * PAGE_SIZE)
# define	MAX_LARGE	(976563 * PAGE_SIZE)

typedef struct s_chunk	t_chunk;
typedef struct s_malloc	t_malloc;
typedef struct s_zone	t_zone;
typedef struct s_block	t_block;

extern t_malloc g_zone;

/*
** ========================================================================== **
** memory chunk struct
** 		h_block =>		head of chunks
** 		remain_size => 	size of biggest free block or size of chunk for LARGE
*/

struct		s_chunk
{
	t_dlst		h_block;
	uint32_t	remain_size;
};

/*
** ========================================================================== **
** blocks struct in chunks
** 
*/

struct		s_block
{
	t_dlst		b_dlst;
	uint32_t	size;
	int			free;
};

/*
** ========================================================================== **
** Zone struct that can be define as TINY or SMALL
** 		head =>		ptr to zone
** 		q_size =>	quantum size (16b / 512b / 4kb - Tiny / Small / Large)
** 		r_size =>	region size (2MB / 16MB / N/A)
*/
struct		s_zone
{
	t_dlst			head;
	uint32_t const	q_size;
	uint32_t const	r_size;
	void			(*ft_malloc)(size_t size, t_zone *zone);
	void			(*ft_realloc)(void *ptr, size_t size, t_zone *zone);
};
/*
** ========================================================================== **
** mall is the env struct
** 		head => 	head of the dlst to have all the blocks
*/

struct		s_malloc
{
	t_zone		zone[3];
};



/*
** ========================================================================== **
** Chunk functions
*/
t_chunk		find_chunk(t_dlst *head, t_chunk *last, size_t size);
t_chunk		add_chunk(t_dlst *head);
#endif
