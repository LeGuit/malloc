/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 17:52:42 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/09 17:48:21 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define GET_B(ptr)	(t_block *)((ptr) - (META_SIZE))

static void		*realloc_new(void *ptr, size_t size)
{
	void			*newptr;

	newptr = malloc(size);
	ft_memcpy(newptr, ptr, ((t_block *)ptr - META_SIZE)->size);
	free(ptr);
	return (newptr);
}

static bool		is_space_realloc(void *ptr, size_t size)
{
	t_block			*next_b;
	t_dlst			tmp;
	size_t			merge_size;

	next_b = (t_block *)(GET_B(ptr))->block_node.next;
	if (next_b < GET_B(ptr))
		return (false);
	tmp = next_b->block_node;
	merge_size = (GET_B(ptr))->size + next_b->size;
	if (!(next_b->free == true && ((GET_B(ptr))->size + next_b->size) >= size))
		return (false);
	(GET_B(ptr))->size = size;
	(GET_B(ptr))->block_node.next = (t_dlst *)((void *)GET_B(ptr) + size);
	next_b = (t_block *)(GET_B(ptr))->block_node.next;
	next_b->block_node = tmp;
	next_b->free = true;
	next_b->size = merge_size - size;
	return (true);
}

void			*realloc(void *ptr, size_t size)
{
	bool			test;
	
ft_printf("REALLOC ptr_adress: %p\tsize: %d\n", ptr, size);
	test = false;
	if (!ptr)
		return (malloc(size));
	if ((test = is_in_chunk(&g_zone.zone[0], ptr) && size < TINY_SIZE)
		|| (test = is_in_chunk(&g_zone.zone[1], ptr) && size < SMALL_SIZE)
		|| (test = is_in_chunk_large(&g_zone.zone[3], ptr)))
	{
		if(is_space_realloc(ptr, size))
			return (ptr);
	}
	else if (test)
		return (realloc_new(ptr, size));
	else
		ft_printf("free error: ptr is not allocated");
	return (NULL);
}
