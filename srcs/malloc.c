/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 11:36:31 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/09 17:46:40 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc	g_zone = {
	(t_zone){
		DLST_HEAD(g_zone.zone[0].chunks_head),
		16,
		TINY_SIZE,
		"TINY",
		&malloc_reg,
		&realloc,
	},
	(t_zone){
		DLST_HEAD(g_zone.zone[1].chunks_head),
		512,
		SMALL_SIZE,
		"SMALL",
		&malloc_reg,
		&realloc,
	},
	(t_zone){
		DLST_HEAD(g_zone.zone[2].chunks_head),
		MAX_LARGE - CHUNK_SIZE,
		MAX_LARGE,
		"LARGE",
		&malloc_large,
		&realloc,
	}
};

void		*malloc(size_t size)
{
	size_t		i;
	size_t		real_size;

	i = 0;
	if (size > MAX_LARGE)
		return (NULL);
ft_printf(C_YELLOW"\nNEW MALLOC:\t\tsize = %d\t"C_RESET, size);
	while (i < 3)
	{
		if (size <= (g_zone.zone[i].r_size))
		{
			real_size = g_zone.zone[i].q_size;
			real_size = (size % real_size == 0 ?
				size : ((size / real_size) + 1) * real_size);
			ft_printf("TYPE: %s\tC_SIZE: %d\tM_SIZE: %d\n", g_zone.zone[i].name, CHUNK_SIZE, META_SIZE);
			{
				show_alloc_mem();
				return (g_zone.zone[i].ft_malloc(real_size, &g_zone.zone[i])); 
			}
		}
		i++;
	}
	return (NULL);
}
