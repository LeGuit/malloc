/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_chunk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 12:05:19 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/06/29 15:08:00 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunk		find_chunk(t_dlst *head, size_t size)
{
	t_dlst		*it;
	t_chunk		chunk;

	while (it->next != head)
	{
		chunk = C_NODE(t_chunk,it);
		if (chunk->remain_size >= size /* + size meta data */)
			return (chunk);
		it = it->next;
	}
	return (add_chunk(head));// need to know the size of the chunk
}
