/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_reg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:02:13 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/02 15:32:57 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"
#include "malloc.h"

#define BLOCK_SIZE(size)	(size + META_SIZE)

static t_block		*split_block(t_chunk *chunk, t_block *free_block,
									size_t size)
{
	t_block				*remain_block;

	remain_block = free_block + BLOCK_SIZE(size); // ALIGN BLOCK
	remain_block->size = chunk->remain_size - BLOCK_SIZE(size);
	remain_block->free = true;
	free_block->size = size;
	free_block->free = false;
	dlst_add_tail(remain_block, chunk->h_block);
	return (free_block + META_SIZE);
}

static t_block		*find_block(t_chunk *chunk, size_t size);
{
	t_block				*free_block;
	t_dlst				*it;

	it = chunk->h_block;
	while ((it = it->next) != chunk->h_block)
	{
		free_block = C_NODE(t_block, it);
		if (free_block->free && free_block->size >= size)
			return (split_block(chunk, free_block, size));
		it = it->next;
	}
	return (NULL);
}

static t_chunk		*add_chunk(t_zone *zone)
{
	t_chunk				*new;
	t_block				*first_block;

	if (!(new = mmap(0, zone->r_size, MMAP_PROT, MMAP_FLAG, -1, 0)))
		return (NULL);
	new->h_block = DLST_INIT(&new->h_block);
	new->remain_size = zone->r_size - CHUNK_SIZE;
	first_block = new + CHUNK_SIZE;
	first_block = DLST_INIT(&first_block->h_dlst);
	first_block->size = new->remain_size - META_SIZE;
	first_block->free = true;
	dlst_add_tail(first_block, new->h_block);
	dlst_add_tail(new, zone->head);
	return (new);
}

static t_chunk		*find_chunk(t_zone *zone, size_t size)
{
	t_dlst				*it;
	t_chunk				*chunk;

	it = zone->head;
	while ((it = it->next) != zone->head)
	{
		chunk = C_NODE(t_chunk,it);
		if (chunk->remain_size >= size + META_SIZE)
			return (chunk);
	}
	return (add_chunk(zone));
}


void				*malloc_reg(size_t size, t_zone *zone)
{
	t_chunk				*chunk;
	t_block				*block;

	chunk = find_chunk(zone, size);
	block = find_block(chunk, size);
	return (block);
}
