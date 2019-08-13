/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 00:30:45 by hgranule          #+#    #+#             */
/*   Updated: 2019/07/30 03:12:30 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	ind;

	ind = 0;
	if (s)
		if (f)
			while (s[ind])
			{
				(*f)(ind, &s[ind]);
				ind++;
			}
}
