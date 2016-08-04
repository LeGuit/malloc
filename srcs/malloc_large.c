/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_large.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:04:31 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/04 13:59:30 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*create_chunk(t_zone *zone, size_t size)
{
	t_chunk				*new;
	t_block				*first_block;

	new = (t_chunk *)mmap(0, zone->r_size, MMAP_PROT, MMAP_FLAG, -1, 0);
	if ((void *)new == MAP_FAILED)
		return (NULL);
	new->blocks_head = DLST_INIT(&new->blocks_head);
	new->remain_size = zone->q_size - (size + CHUNK_SIZE + META_SIZE);
	dlst_add_tail(&new->blocks_head, &zone->chunks_head);
	first_block = (t_block *)(new + CHUNK_SIZE);
	first_block->size = size;
	first_block->free = false;
	dlst_add_tail(&first_block->b_dlst, &new->blocks_head);
	return (first_block + META_SIZE);
}

void			*malloc_large(size_t size, t_zone *zone)
{
	t_block				*block;

	block = create_chunk(zone, size);
	return (block);
}
