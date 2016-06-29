/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 17:52:42 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/06/29 17:56:03 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc	g_zone = {
	{
		DLST_INIT(&g_zone.tiny),
		16,
		TINY_SIZE,
		&malloc_reg,
		&realloc_reg,
	},
	{
		DLST_INIT(&g_zone.small),
		512,
		SMALL_SIZE,
		&malloc_reg,
		&realloc_reg,
	},
	{
		DLST_INIT(&g_zone.large),
		MAX_LARGE - CHUNK_SIZE,
		MAX_LARGE,
		&malloc_large,
		&realloc_large
	}
};

void		*realloc(void *ptr, size_t size)
{
	uint32_t	i;

	i = 0;
	while (i < 3)
	{
		if (size <= g_zone[i].q_size)
			return (g_zone[i]->ft_realloc(ptr, size, g_zone[i]));
	}
	return (NULL);
}
