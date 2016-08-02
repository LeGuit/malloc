/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 11:47:56 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/02 15:21:29 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"

# include <stdbool.h>
# include <sys/mman.h>

/*
** ========================================================================== **
** ALIGN4 =>		check if align 4 or 8
** 					this define align to the next 4 multiple
** CHUNK_SIZE =>	size of the header of a chunk
*/

# define CHUNK_SIZE		sizeof(t_chunk)
# define META_SIZE		sizeof(t_block)
/*
** Temp getpagesize() = 4096 because of the non initialise
*/
# define PAGE_SIZE		(4096)
# define TINY_SIZE		(521 * PAGE_SIZE)
# define SMALL_SIZE		(4096 * PAGE_SIZE)
# define MAX_LARGE		(976563 * PAGE_SIZE)

/*
** ========================================================================== **
** Macro for mmap PROT && FLAG
*/
# define MMAP_PROT			PROT_READ | PROT_WRITE
# define MMAP_FLAG			MAP_ANON | MAP_PRIVATE

typedef struct s_chunk	t_chunk;
typedef struct s_malloc	t_malloc;
typedef struct s_zone	t_zone;
typedef struct s_block	t_block;
typedef enum e_z_name	t_z_name;

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
*/

struct		s_block
{
	t_dlst		b_dlst;
	uint32_t	size;
	bool		free;
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
	char const		*name;
	void			*(*ft_malloc)(size_t size, t_zone *zone);
	void			*(*ft_realloc)(void *ptr, size_t size, t_zone *zone);
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
t_chunk			find_chunk(t_dlst *head, t_chunk *last, size_t size);
t_chunk			add_chunk(t_dlst *head);

/*
** ========================================================================== **
** Print allocated memory sorted by type from TINY to LARGE
** Format :
** 		TYPE : ADR of chunk
** 			range of block : size of it
*/

void			show_alloc_mem(void);

/*
** ========================================================================== **
** Malloc part
*/

void			*malloc_reg(size_t size, t_zone *zone);
void			*malloc_large(size_t size, t_zone *zone);


/*
** ========================================================================== **
** Free part
*/

int				free_block(void *ptr);
void			free(void *ptr);

/*
** ========================================================================== **
** Realloc part
*/
void			*realloc_reg(void *ptr, size_t size, t_zone *zone);
void			*realloc_large(void *ptr, size_t size, t_zone *zone);

/*
** ========================================================================== **
** Tools
*/
int				is_in_block(t_chunk *c);
int				is_in_chunk(t_zone *z, void *ptr);
// int				is_in_chunk_l(t_zone *z, void *ptr);
#endif
