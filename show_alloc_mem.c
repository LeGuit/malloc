/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 14:34:29 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/07/06 15:26:24 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		show_large(t_zone *z)
{
	
}

static int		show_blocks(t_chunk *c)
{
	uint32_t		sum;
	t_dlst			*it;
	t_block			*b;

	sum = 0;
	it = c->h_block;
	while ((it = it->next) != c->h_block)
	{
		b = C_NODE(t_block, it);
		ft_printf("%#X - %#X : %u\n", )
	}

}

static int		show_tiny_small(t_zone *z)
{
	t_dlst			*it;
	t_chunk			*c;
	uint32_t		size_block;

	it = z->head;
	size_block = 0;
	while ((it = it->next) != z->head)
	{
		c = C_NODE(t_chunk, it);
		ft_printf("%s : %#X\n", z->name, c);
		size_block += show_blocks(c);
	}
	return (size_block);
}

void			show_alloc_mem(void)
{
	uint32_t		total;

	total += show_tiny_small(g_zone[0]);
	total += show_tiny_small(g_zone[1]);
	total += show_large(g_zone[2]);
	ft_printf("Total : %u octets", total);
	return ;	
}
