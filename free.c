/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 16:25:14 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/07/12 19:13:02 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			free(void *ptr)
{
	if (is_in_chunk(g_zone[0],ptr) && is_in_chunk(g_zone[1],ptr)
		&& is_in_chunk_l(g_zone[2],ptr))
	{
		ft_printf("free error: ptr is not allocated");
		return ;
	}
}
