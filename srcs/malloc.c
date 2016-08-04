/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 11:36:31 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/04 12:18:28 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc	g_zone = {
	(t_zone){
		DLST_INIT(&g_zone.zone[0].chunks_head),
		16,
		TINY_SIZE,
		"TINY",
		&malloc_reg,
		&realloc,
	},
	(t_zone){
		DLST_INIT(&g_zone.zone[1].chunks_head),
		512,
		SMALL_SIZE,
		"SMALL",
		&malloc_reg,
		&realloc,
	},
	(t_zone){
		DLST_INIT(&g_zone.zone[2].chunks_head),
		MAX_LARGE - CHUNK_SIZE,
		MAX_LARGE,
		"LARGE",
		&malloc_large,
		&realloc,
	}
};

void		*malloc(size_t size)
{
	uint32_t	i;

	i = 0;
	if (size > MAX_LARGE)
		return (NULL);
	while (i < 3)
	{
	ft_printf("malloc\n");
		if (size <= g_zone.zone[i].q_size)
			return (g_zone.zone[i].ft_malloc(size, &g_zone.zone[i]));
	}
	return (NULL);
}
