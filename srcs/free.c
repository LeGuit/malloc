/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 16:25:14 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/02 14:10:14 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			free(void *ptr)
{
	if (is_in_chunk(&g_zone.zone[0], ptr) && is_in_chunk(&g_zone.zone[1], ptr)
		/*&& is_in_chunk_l(&g_zone.zone[2], ptr)*/)
	{
		ft_printf("free error: ptr is not allocated");
		return ;
	}
	free_block(ptr);
}
