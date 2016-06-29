/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoodwar <gwoodwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 11:47:56 by gwoodwar          #+#    #+#             */
/*   Updated: 2016/06/29 12:17:48 by gwoodwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"

/*
** ========================================================================== **
** check if align 4 or 8
** this define align to the next 4 multiple
*/
# define	ALIGN4(x) (((((x) - 1) >> 2) << 2) + 4)

typedef struct s_chunk	t_chunk;
typedef struct s_mall	t_mall;

/*
** ========================================================================== **
** memory chunk struct
** 		size => size of the chunk
** 		dlst => ptr to next and prev chunk
** 		free => an int to know if chunk is free or not
*/

struct		s_chunk
{
	size_t		size;
	t_dlst		dlst;
	int			free;
};

/*
** ========================================================================== **
** mall is the env struct
** 		head => head of the dlst to have all the blocks
*/

struct		s_mall
{
	t_dlst		head;
};
#endif
