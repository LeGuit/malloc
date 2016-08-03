/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 17:52:42 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/08/03 12:37:07 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*realloc(void *ptr, size_t size)
{
	if (is_in_chunk(&g_zone.zone[0], ptr) == true
		|| is_in_chunk(&g_zone.zone[1], ptr) == true)
		realloc_reg(ptr);
	else if (is_in_chunk_large(&g_zone.zone[2], ptr) == true)
		realloc_large(ptr);
	else
		ft_printf("free error: ptr is not allocated");
	return ;
}
