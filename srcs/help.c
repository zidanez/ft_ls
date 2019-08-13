/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 21:55:39 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/08/10 21:56:09 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		help_put_time(const t_file *fi, char tds)
{
	if (tds)
		put_time(ctime(&fi->st.st_atimespec.tv_sec),
		fi->st.st_mtimespec.tv_sec,
		fi->st.st_atimespec.tv_sec,
		fi->st.st_ctimespec.tv_sec);
	else
		put_time(ctime(&fi->st.st_mtimespec.tv_sec),
		fi->st.st_mtimespec.tv_sec,
		fi->st.st_atimespec.tv_sec,
		fi->st.st_ctimespec.tv_sec);
}
