/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 16:48:10 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/09 14:05:13 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*merge_blocks(t_block *prev, t_block *cur)
{
	prev->size += cur->size + META_SIZE; //Diff entre fin et debut align
	dlst_del_entry(&cur->block_node);
	return (prev);
}

static void		merge_free(void *ptr)
{
	t_block			*b;
	t_block			*adj_b;

	b = (t_block *)(ptr - META_SIZE);
	b->free = true;
	// if ((adj_b = CONTAINEROF(b, t_block, block_node.prev)->free))
	// 	b = merge_blocks(adj_b, b);
	// if ((adj_b = CONTAINEROF(b, t_block, block_node.next)->free))
	// 	b = merge_blocks(b, adj_b);
}

void			free_block(void *ptr)
{
	merge_free(ptr);
	return ;
}

void			free_large(void *ptr)
{
	t_chunk			*c;
	t_block			*b;

	c = (t_chunk *)(ptr - CHUNK_SIZE);
	b = (t_block *)(c + CHUNK_SIZE);
	if (!(munmap(c, b->size + CHUNK_SIZE + META_SIZE) == -1))
		ft_printf("free large error");
	dlst_del_entry(&c->blocks_head);
	return ;
}
