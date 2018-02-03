/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 02:18:12 by aalves            #+#    #+#             */
/*   Updated: 2018/02/03 05:07:08 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H


# include <stdlib.h>
# include <sys/mman.h>
# include "libft.h"


# define TINY 128
# define SMALL 4096

struct	s_alloc_header
{
	t_list_head	list;
	size_t		size;
	uint8_t		free;
};

typedef struct s_alloc_header	t_alloc_header;


void	*ft_malloc(size_t size);





#endif
