/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 17:52:42 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/03 16:32:14 by gwoodwar         ###   ########.fr       */
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

	next_b = GET_B(ptr)->b_dlst->next;
	tmp = next_b->b_dlst;
	if (next_b->free == true && (GET_B(ptr)->size + next_b->size) >= size)
	{
		GET_B(ptr)->size = size;
		GET_B(ptr)->b_dlst->next = GET_B(ptr) + size;
		next_b = GET_B(ptr)->b_dlst->next;
		next_b->b_dlst = tmp;
		next_b->free = true;
		next_b->size = b_dlst->next (size - GET_B(ptr)->size);
	}
	return (true);
}

void			*realloc(void *ptr, size_t size)
{
	bool			test;

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
