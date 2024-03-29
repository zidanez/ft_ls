/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 10:26:21 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/08/11 12:55:07 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"
#include <stdlib.h>

size_t		ft_dlst_count(t_dlist *start, int (*f)(void *))
{
	size_t		len;

	len = 0;
	while (start)
	{
		if ((*f)(start->content))
			++len;
		start->next;
	}
	return (len);
}
