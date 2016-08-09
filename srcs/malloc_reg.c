/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_reg_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 15:07:14 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/09 16:59:18 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_dlst.h"
#include "malloc.h"

static t_block		*split_block(t_block *block, size_t size)
{
	t_block				*next_block;

ft_printf("split_block\tblock_size: %d\trequest_size: %d\n", block->size, size);
	if (block->size == size)
	{
		block->free = false;

		ft_printf("\tReturned splitless ptr: %p\tsize of block = %8d\n", block, block->size);
		
		return (block);
	}
	next_block = (void *)(block + 1) + size;
	*next_block = (t_block){DLST_HEAD_NULL, block->size - (size + META_SIZE), true};
	dlst_add_head(&next_block->block_node, &block->block_node);
	block->size = size;
	block->free = false;

ft_printf(C_CYAN"\tNext block adress: %p is_free: %d size of block = %8d\n"C_RESET, next_block, next_block->free, next_block->size);
ft_printf("\tReturned ptr: %p\tsize of block = %8d\n", block, block->size);
ft_printf("BLOCK + 1: %p\tBLOCK + META: %p\n", block + 1, block + META_SIZE);
	return (block);
}

static t_chunk		*create_chunk(t_zone *zone)
{
	t_chunk				*chunk;
	t_block				*block;

	ft_printf("add_chunk\tregion size: %d q_size: %d\n", zone->r_size, zone->q_size);
	
	chunk = (t_chunk *)mmap(0, zone->r_size, MMAP_PROT, MMAP_FLAG, -1, 0);
	if (chunk == MAP_FAILED)
		return (NULL);
	*chunk = (t_chunk){DLST_HEAD_NULL, DLST_HEAD_NULL};
	DLST_HEAD_INIT(chunk->blocks_head);
	dlst_add_tail(&chunk->chunk_node, &zone->chunks_head);


	block = (t_block *)(chunk + 1);
	*block = (t_block){
		DLST_HEAD_NULL,
		zone->r_size - CHUNK_SIZE - META_SIZE,
		true
	};
	dlst_add_tail(&block->block_node, &chunk->blocks_head);


	ft_printf(C_RED"\tChunk adress: %p\tsize_of_block:%d\n"C_RESET, chunk, block->size);
	ft_printf(C_MAGENT"\tFirst_B adress: %p\tblock_size:%d\tis_free: %d\n"C_RESET, block, block->size, block->free);
	return (chunk);
}

static t_block		*available_block_in_chunk(t_chunk *chunk, size_t size)
{
	t_dlst				*it;
	t_block				*block;

	ft_printf("available_block_in_chunk?\n");
	it = chunk->blocks_head.next;
	while (it != &chunk->blocks_head)
	{
		block = CONTAINEROF(it, t_block, block_node);
		ft_printf(C_CYAN"\tBlock adress: %p is_free: %d size of block = %8d\n"C_RESET, it, block->free, block->size);
		if (block->free && block->size >= size)
			return (block);
		it = it->next;
	}
	return (NULL);
}

static t_block		*available_block_in_zone(t_zone *zone, size_t size)
{
	t_dlst				*it;
	t_chunk				*chunk;
	t_block				*block;

	it = zone->chunks_head.next;
	while (it != &zone->chunks_head)
	{
		ft_printf(C_GREEN"\tChunk adress: %p\n"C_RESET, it);
		chunk = CONTAINEROF(it, t_chunk, chunk_node);
		if ((block = available_block_in_chunk(chunk, size)))
			return (block);
		it = it->next;
	}
	return (NULL);
}

void				*malloc_reg(size_t size, t_zone *zone)
{
	t_chunk				*chunk;
	t_block				*block;

	block = available_block_in_zone(zone, size);
	if (block == NULL)
	{
		ft_printf("no_block_available\tcreating chunk...\n");
		chunk = create_chunk(zone);
		if (chunk == NULL)
			return (NULL);
		block = available_block_in_chunk(chunk, size);
	}
	return (split_block(block, size) + 1);
}
