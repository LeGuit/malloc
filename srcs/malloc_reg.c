/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_reg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:02:13 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/04 13:47:28 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"
#include "malloc.h"

#define BLOCK_SIZE(size)	(size + META_SIZE)

static t_block		*split_block(t_chunk *chunk, t_block *free_block,
									size_t size)
{
	t_block				*remain_block;
ft_printf("split_block\n");
	remain_block = free_block + BLOCK_SIZE(size); // ALIGN BLOCK
	remain_block->size = chunk->remain_size - BLOCK_SIZE(size);
	remain_block->free = true;
	free_block->size = size;
	free_block->free = false;
	dlst_add_tail(&remain_block->b_dlst, &chunk->blocks_head);
	return (free_block + META_SIZE);
}

static t_block		*find_block(t_chunk *chunk, size_t size)
{
	t_block				*free_block;
	t_dlst				*it;

ft_printf("find_block\n");
	it = chunk->blocks_head.next;
	while (it != &chunk->blocks_head)
	{
	ft_printf("find_block_while\n");		
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

ft_printf("add_chunk\n");
	new = (t_chunk *)mmap(0, zone->r_size, MMAP_PROT, MMAP_FLAG, -1, 0);
	if ((void *)new == MAP_FAILED)
		return (NULL);
	new->blocks_head = DLST_INIT(&new->blocks_head);
	new->remain_size = zone->r_size - CHUNK_SIZE;
	dlst_add_tail(&new->blocks_head, &zone->chunks_head);
	first_block = (t_block *)(new + CHUNK_SIZE);
	first_block->size = new->remain_size - META_SIZE;
	first_block->free = true;
	dlst_add_tail(&first_block->b_dlst, &new->blocks_head);
	return (new);
}

static t_chunk		*find_chunk(t_zone *zone, size_t size)
{
	t_dlst				*it;
	t_chunk				*chunk;
ft_printf("find_chunk\n");
	it = zone->chunks_head.next;
	while (it != &zone->chunks_head)
	{
		chunk = C_NODE(t_chunk, it);
		if (chunk->remain_size >= size + META_SIZE)
			return (chunk);
		it = it->next;
	}
ft_printf("no_chunks_available\n");
	return (add_chunk(zone));
}

void				*malloc_reg(size_t size, t_zone *zone)
{
	t_chunk				*chunk;
	t_block				*block;
ft_printf("m_reg\n");
	if (!(chunk = find_chunk(zone, size)))
		return (NULL);
ft_printf("after_find_chunk\n");
	block = find_block(chunk, size);
	return (block);
}
