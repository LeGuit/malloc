/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 17:52:42 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/07/12 18:09:26 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
