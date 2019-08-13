/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 17:38:41 by fnancy            #+#    #+#             */
/*   Updated: 2019/08/11 13:56:44 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		create_d_flag(char **argv, int n, int argc, t_nowdir **nowdir)
{
	char	*name;
	t_file	*file;

	init_dir(nowdir);
	(*nowdir)->name = ft_strdup("");
	(*nowdir)->c_files = argc - n;
	while (n < argc)
	{
		name = argv[n];
		file = fill_file(name, (*nowdir)->name, ft_strlen(name));
		if (file->name_len > (*nowdir)->m_fname)
			(*nowdir)->m_fname = file->name_len;
		if (file->blck_size > (*nowdir)->m_blck_size)
			(*nowdir)->m_blck_size = file->blck_size;
		ft_dlstpush(&(*nowdir)->file, ft_dlstnew_cc((t_file *)file,\
					sizeof(t_file)));
		n++;
	}
}
