/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_is_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 19:12:09 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/04 12:18:25 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

bool			is_in_block(t_chunk *c, void *ptr)
{
	t_dlst			*it;
	t_block			*b;

	it = &c->c_dlst;
	while ((it = it->next) != &c->c_dlst)
	{
		b = C_NODE(t_block, it);
		if (ptr > (void *)&b->b_dlst && ptr < (void *)&b->b_dlst + b->size)
			return (true);
	}
	return (false);
}

bool			is_in_chunk(t_zone *z, void *ptr)
{
	t_dlst			*it;
	t_chunk			*c;

	it = &z->chunks_head;
	while ((it = it->next) != &z->chunks_head)
	{
		c = C_NODE(t_chunk, it);
		if (ptr > (void *)&c->c_dlst && ptr < ((void *)&c->c_dlst + z->r_size))
			if (!is_in_block(c, ptr))
				return (false);
	}
	return (true);
}

bool			is_in_chunk_large(t_zone *z, void *ptr)
{
	t_dlst			*it;
	t_chunk			*c;

	it = &z->chunks_head;
	while ((it = it->next) != &z->chunks_head)
	{
		c = C_NODE(t_chunk, it);
		if (ptr == (void *)&c->c_dlst + CHUNK_SIZE)
			return (true);
	}
	return (false);
}
