/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 14:34:29 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/09 17:34:26 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define BLOCK_ADR(ptr)		(ptr + META_SIZE)

static int		show_large(t_zone *z)
{
	t_dlst			*it;
	t_chunk			*c;
	t_block			*b;
	uint32_t		sum;

	sum = 0;
	it = z->chunks_head.next;
	while (it != &z->chunks_head)
	{
		c = C_NODE(t_chunk, it);
		b = b + CHUNK_SIZE + META_SIZE;
		ft_printf("%s : %#x\n", z->name, c);
		ft_printf("%#x - %#x : %u octets", b, b + b->size, b->size);
		sum += b->size;
		it = it->next;
	}
	return (sum);
}

static int		show_blocks(t_chunk *c)
{
	uint32_t		sum;
	t_dlst			*it;
	t_block			*b;

	sum = 0;
	it = c->blocks_head.next;
	while (it != &c->blocks_head)
	{
		b = C_NODE(t_block, it);
		if (b->free == false)
		{
			ft_printf("%#x - %#x : %u octets\n",
				BLOCK_ADR(b), BLOCK_ADR(b + b->size), b->size);
			sum += b->size;
		}
		it = it->next;
	}
	return (sum);
}

static int		show_tiny_small(t_zone *z)
{
	t_dlst			*it;
	t_chunk			*c;
	uint32_t		size_block;

	it = z->chunks_head.next;
	size_block = 0;
	while (it != &z->chunks_head)
	{
		c = C_NODE(t_chunk, it);
		ft_printf("%s : %#x\n", z->name, c);
		size_block += show_blocks(c);
		it = it->next;
	}
	return (size_block);
}

void			show_alloc_mem(void)
{
	uint32_t		total;

	total = 0;
	total += show_tiny_small(&g_zone.zone[0]);
	total += show_tiny_small(&g_zone.zone[1]);
	total += show_large(&g_zone.zone[2]);
	ft_printf("Total : %u octets\n", total);
	return ;
}
