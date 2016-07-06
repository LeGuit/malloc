/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 11:36:31 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/07/06 15:08:19 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"
#include "malloc.h"

t_malloc	g_zone = {
	{
		DLST_INIT(&g_zone.tiny),
		16,
		TINY_SIZE,
		"TINY",
		&malloc_reg,
		&realloc_reg,
	},
	{
		DLST_INIT(&g_zone.small),
		512,
		SMALL_SIZE,
		"SMALL",
		&malloc_reg,
		&realloc_reg,
	},
	{
		DLST_INIT(&g_zone.large),
		MAX_LARGE - CHUNK_SIZE,
		MAX_LARGE,
		"LARGE",
		&malloc_large,
		&realloc_large
	}
};

void		*malloc(size_t size)
{
	uint32_t	i;

	i = 0;
	while (i < 3)
	{
		if (size <= g_zone[i].q_size)
			return (g_zone[i]->ft_malloc(size, g_zone[i]));
	}
	return (NULL);
}
