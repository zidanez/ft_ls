/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 04:13:44 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/08/11 12:57:13 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"
#include "ft_mem.h"

void		ft_strmcpy(char **dst, const char *src)
{
	size_t	len;

	if (!src)
	{
		(*dst) = NULL;
		return ;
	}
	len = ft_strlen(src);
	(*dst) = (char*)malloc(sizeof(char) * len);
	ft_memcpy((*dst), src, len);
	(*dst)[len] = 0;
}
