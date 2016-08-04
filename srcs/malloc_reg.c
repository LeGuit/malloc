/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_reg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:02:13 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/04 17:52:33 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"
#include "malloc.h"

static t_block		*split_block(t_chunk *chunk, t_block *block,
									size_t size)
{
	t_block				*next_block;

ft_printf("split_block\tblock_size: %d\trequest_size: %d\n", block->size, size);

	next_block = (void *)(block + 1) + size;
	chunk->remain_size -= size + META_SIZE;
	*next_block = (t_block){DLST_HEAD_NULL, block->size - (size + META_SIZE), true};
	dlst_add_head(&next_block->block_node, &block->block_node);
	block->size = size;
	block->free = false;

ft_printf(C_CYAN"\tNext block adress: %p is_free: %d size of block = %8d\n"C_RESET, next_block, next_block->free, next_block->size);
	
	return (block + 1);
}

static t_block		*find_block(t_chunk *chunk, size_t size)
{
	t_block				*block;
	t_dlst				*it;

ft_printf("find_block\n");
	it = chunk->blocks_head.next;
	while (it != &chunk->blocks_head)
	{
		block = CONTAINEROF(it, t_block, block_node);
ft_printf(C_CYAN"\tBlock adress: %p is_free: %d size of block = %8d\n"C_RESET, it, block->free, block->size);
		if (block->free && block->size >= size)
			return (split_block(chunk, block, size));
		it = it->next;
	}
	ft_printf("end_find_block_while\n");
	return (NULL);
}

static t_chunk		*add_chunk(t_zone *zone)
{
	t_chunk				*chunk;
	t_block				*block;

	ft_printf("add_chunk\tregion size: %d q_size: %d\n", zone->r_size, zone->q_size);
	
	chunk = (t_chunk *)mmap(0, zone->r_size, MMAP_PROT, MMAP_FLAG, -1, 0);
	if (chunk == MAP_FAILED)
		return (NULL);
	*chunk = (t_chunk){DLST_HEAD_NULL, DLST_HEAD_NULL,
		zone->r_size - CHUNK_SIZE - META_SIZE};
	DLST_HEAD_INIT(chunk->blocks_head);
	dlst_add_tail(&chunk->chunk_node, &zone->chunks_head);
	block = (t_block*)(chunk + 1);
	*block = (t_block){DLST_HEAD_NULL, chunk->remain_size, true};
	dlst_add_tail(&block->block_node, &chunk->blocks_head);

	ft_printf(C_RED"\tChunk adress: %p\tremain_size:%d\n"C_RESET, chunk, chunk->remain_size);
	ft_printf(C_MAGENT"\tFirst_B adress: %p\tblock_size:%d\tis_free: %d\n"C_RESET, block, block->size, block->free);
	return (chunk);
}

static t_chunk		*find_chunk(t_zone *zone, size_t size)
{
	t_dlst				*it;
	t_chunk				*chunk;

	it = zone->chunks_head.next;
ft_printf("find_chunk\n");
	while (it != &zone->chunks_head)
	{
		chunk = CONTAINEROF(it, t_chunk, chunk_node);
ft_printf(C_GREEN"\tChunk adress: %p size of chunk remain = %8d\n"C_RESET, it, chunk->remain_size);
		if (chunk->remain_size >= size + META_SIZE)
		{
ft_printf("\tChunk found adress: %p\n", chunk);
			return (chunk);
		}
		it = it->next;
	}
ft_printf("no_chunks_available\n");
	return (add_chunk(zone));
}

void				*malloc_reg(size_t size, t_zone *zone)
{
	t_chunk				*chunk;
	t_block				*block;
ft_printf("malloc_reg\n");
	if (!(chunk = find_chunk(zone, size)))
		return (NULL);
ft_printf("after_find_chunk\n");
	block = find_block(chunk, size);
ft_printf("\tReturned ptr: %p\tsize of block = %8d\n", block, (block - 1)->size);
	return (block);
}
