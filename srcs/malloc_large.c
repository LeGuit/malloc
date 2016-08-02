/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_large.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:04:31 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/02 15:33:04 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*create_chunk(t_zone *zone, size_t size)
{
	t_chunk				*new;
	t_block				*first_block;

	new = mmap(0, size + CHUNK_SIZE + META_SIZE, MMAP_PROT, MMAP_FLAG, -1, 0);
	new->h_block = DLST_INIT(&new->h_block);
	new->remain_size = 0;
	first_block = new + CHUNK_SIZE;
	first_block = DLST_INIT(&first_block->h_dlst);
	first_block->size = size;
	first_block->free = false;
	dlst_add_tail(first_block, new->h_block);
	dlst_add_tail(new, zone->head);
	return (first_block + META_SIZE);
}

void			*malloc_large(size_t size, t_zone *zone)
{
	t_block				*block;

	block = create_chunk(zone, size);
	return (block);
}