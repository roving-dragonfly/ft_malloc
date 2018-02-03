/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 03:11:11 by aalves            #+#    #+#             */
/*   Updated: 2018/02/03 03:51:13 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Singletons to deliver chunks lists
*/

t_list_head	*get_alloc_list()
{
	static t_list_head list;

	if (!list.prev && !list.next)
		init_list_head(&list);
	return (&list);
}

t_list_head	*get_free_list()
{
	static t_list_head list;

	if (!list.prev && !list.next)
		init_list_head(&list);
	return (&list);
}
