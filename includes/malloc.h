/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 11:47:56 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/04 12:23:10 by gwoodwar         ###   ########.fr       */
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

# define CHUNK_SIZE		(uint32_t)sizeof(t_chunk)
# define META_SIZE		(uint32_t)sizeof(t_block)

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
** 		blocks_head =>	head of blocks in a chunk
** 		remain_size => 	size of biggest free block or size of chunk for LARGE
*/

struct		s_chunk
{
	t_dlst		blocks_head;
	uint32_t	remain_size;
};

/*
** ========================================================================== **
** blocks struct in chunks
** 		b_dslt		=> dlist of blocks
** 		size		=> size of a block (without META)
** 		free		=> status of the block
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
** 	chunks_head =>		Head of chunks
** 	q_size 		=>		quantum size (16b / 512b / 4kb - Tiny / Small / Large)
** 	r_size 		=>		region size (2MB / 16MB / N/A)
*/

struct		s_zone
{
	t_dlst			chunks_head;
	uint32_t const	q_size;
	uint32_t const	r_size;
	char const		*name;
	void			*(*ft_malloc)(size_t size, t_zone *zone);
	void			*(*ft_realloc)(void *ptr, size_t size);
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

void			free_block(void *ptr);
void			free_large(void *ptr);
void			free(void *ptr);

/*
** ========================================================================== **
** Realloc part
** Those func needs to be done
*/
void			*realloc(void *ptr, size_t size);

/*
** ========================================================================== **
** Tools
*/
bool			is_in_block(t_chunk *c, void *ptr);
bool			is_in_chunk(t_zone *z, void *ptr);
bool			is_in_chunk_large(t_zone *z, void *ptr);

/*
** ========================================================================== **
** DEBUG
*/

#include <stdio.h>

#define DEBUG_STEP			printf("TOTO");
#define D_PRINT(f,...)		printf(f, ##__VA_ARGS__);fflush(stdout)
#endif
