/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 08:31:40 by hgranule          #+#    #+#             */
/*   Updated: 2019/07/30 05:41:59 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strrchr(const char *str, int ch)
{
	size_t		str_len;
	char		*finder;
	char		chr;

	str_len = ft_strlen(str);
	finder = (char *)(str + str_len);
	str_len += 1;
	chr = (char)ch;
	while (str_len--)
	{
		if (*finder == chr)
			return (finder);
		finder--;
	}
	return (0);
}
