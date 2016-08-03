/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 16:25:14 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/03 12:15:19 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			free(void *ptr)
{
	if (is_in_chunk(&g_zone.zone[0], ptr) == true
		|| is_in_chunk(&g_zone.zone[1], ptr) == true)
		free_block(ptr);
	else if (is_in_chunk_large(&g_zone.zone[2], ptr) == true)
		free_large(ptr);
	else
		ft_printf("free error: ptr is not allocated");
	return ;
}
