/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_is_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 19:12:09 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/09 14:01:43 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

bool			is_in_block(t_chunk *c, void *ptr)
{
	t_dlst			*it;
	t_block			*b;

	it = c->blocks_head.next;
	while (it != &c->blocks_head)
	{
		b = C_NODE(t_block, it);
		if (ptr > (void *)&b->block_node
			&& ptr < (void *)&b->block_node + b->size)
			return (true);
		it = it->next;
	}
	return (false);
}

bool			is_in_chunk(t_zone *z, void *ptr)
{
	t_dlst			*it;
	t_chunk			*c;

	it = z->chunks_head.next;
	while (it != &z->chunks_head)
	{
		c = C_NODE(t_chunk, it);
		if (ptr > (void *)&c->blocks_head
			&& ptr < ((void *)&c->blocks_head + z->r_size))
			if (!is_in_block(c, ptr))
				return (false);
		it = it->next;
	}
	return (true);
}

bool			is_in_chunk_large(t_zone *z, void *ptr)
{
	t_dlst			*it;
	t_chunk			*c;

	it = z->chunks_head.next;
	while (it != &z->chunks_head)
	{
		c = C_NODE(t_chunk, it);
		if (ptr == (void *)&c->blocks_head + CHUNK_SIZE)
			return (true);
		it = it->next;
	}
	return (false);
}
