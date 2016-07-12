/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 16:48:10 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/07/12 18:51:11 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*merge_blocks(t_block *prev, t_block *cur)
{
	prev->size += cur->size + META_SIZE; //Diff entre fin et debut align
	dlst_del_entry(cur->dlst);
}

static void		merge_free(void *ptr)
{
	t_block			*b;
	t_block			*adj_b;

	b = ptr - META_SIZE;
	b->free = true;
	if ((adj_b = C_NODE(b->b_dlst->prev))->free)
		b = merge_blocks(adj_b, b);
	if ((adj_b = C_NODE(b->b_dlst->next))->free)
		b = merge_blocks(b, adj_b);
}

int				free_block(void *ptr)
{
	merge_free(ptr);
	return (0);
}
