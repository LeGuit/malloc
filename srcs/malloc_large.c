/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_large.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:04:31 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/04 16:15:13 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*create_chunk(t_zone *zone, size_t size)
{
	t_chunk				*chunk;
	t_block				*block;

	chunk = (t_chunk *)mmap(0, zone->r_size, MMAP_PROT, MMAP_FLAG, -1, 0);
	if (chunk == MAP_FAILED)
		return (NULL);
	*chunk = (t_chunk){DLST_HEAD_NULL, DLST_HEAD_NULL,
		zone->r_size - CHUNK_SIZE - META_SIZE};
	DLST_HEAD_INIT(chunk->blocks_head);
	dlst_add_tail(&chunk->blocks_head, &zone->chunks_head);
	block = (t_block*)(chunk + 1);
	*block = (t_block){DLST_HEAD_NULL, chunk->remain_size, false};
	dlst_add_tail(&block->block_node, &chunk->blocks_head);
	return (block + 1);
}

void			*malloc_large(size_t size, t_zone *zone)
{
	t_block				*block;

	block = create_chunk(zone, size);
	return (block);
}

	
