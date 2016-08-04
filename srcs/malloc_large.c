/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_large.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:04:31 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/04 12:18:27 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*create_chunk(t_zone *zone, size_t size)
{
	t_chunk				*new;
	t_block				*first_block;

	new = mmap(0, size + CHUNK_SIZE + META_SIZE, MMAP_PROT, MMAP_FLAG, -1, 0);
	new->c_dlst = DLST_INIT(&new->c_dlst);
	new->remain_size = zone->q_size - (size + CHUNK_SIZE + META_SIZE);
	first_block = (t_block *)(new + CHUNK_SIZE);
	first_block->b_dlst = DLST_INIT(&first_block->b_dlst);
	first_block->size = size;
	first_block->free = false;
	dlst_add_tail(&first_block->b_dlst, &new->c_dlst);
	dlst_add_tail(&new->c_dlst, &zone->chunks_head);
	return (first_block + META_SIZE);
}

void			*malloc_large(size_t size, t_zone *zone)
{
	t_block				*block;

	block = create_chunk(zone, size);
	return (block);
}
