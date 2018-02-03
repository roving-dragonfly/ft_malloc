/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 01:18:51 by aalves            #+#    #+#             */
/*   Updated: 2018/02/03 05:06:58 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "malloc.h"


void	*alloc_large(size_t size)
{
	pt = mmap(NULL, 4096, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
	add_to_large_list();
}

void	*ft_malloc(size_t size)
{

	 void *page;
	 printf("page : %p\n", page);



	if (size <= TINY)
	{
		//if no page get one and add to the list
		//all calls <32 get 32 cuz fu biatch
	}
	else if (size <= SMALL)
	{
		//if no page alloc 4 of them and alloc 128 bytes area
	}
	else
	{
		//get size/4096 + 1 * (size%4096) pages and put the shit here
		return (alloc_large(size));
	}

	return (0);
}
