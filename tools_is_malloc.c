/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_is_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 19:12:09 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/07/12 19:12:28 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				is_in_block(t_chunk *c)
{
	t_dlst			*it;
	t_block			*b;

	it = c->h_block;
	while((it = it->next) != c->h_block)
	{
		b = C_NODE(t_block, it);
		if (ptr > b && ptr < b + b->size)
			return (0);
	}
	return (1);
}

int				is_in_chunk(t_zone *z, void *ptr)
{
	t_dlst			*it;
	t_chunk			*c;

	it = z->head;
	while((it = it->next) != z->head)
	{
		c = C_NODE(t_chunk, it);
		if (ptr > c && ptr < c + c->r_size)
			if (!is_block(c, ptr))
				return(free_block(ptr));
	}
	return (1);
}	
