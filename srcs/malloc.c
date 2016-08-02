/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 11:36:31 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/02 16:20:59 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc	g_zone = {
	(t_zone){
		DLST_INIT(&g_zone.zone[0].head),
		16,
		TINY_SIZE,
		"TINY",
		&malloc_reg,
		&realloc_reg,
	},
	(t_zone){
		DLST_INIT(&g_zone.zone[1].head),
		512,
		SMALL_SIZE,
		"SMALL",
		&malloc_reg,
		&realloc_reg,
	},
	(t_zone){
		DLST_INIT(&g_zone.zone[2].head),
		MAX_LARGE - CHUNK_SIZE,
		MAX_LARGE,
		"LARGE",
		&malloc_large,
		&realloc_large,
	}
};

void		*malloc(size_t size)
{
	uint32_t	i;

	i = 0;
	while (i < 3)
	{
		if (size <= g_zone.zone[i].q_size)
			return (g_zone.zone[i].ft_malloc(size, &g_zone.zone[i]));
	}
	return (NULL);
}
