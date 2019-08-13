/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:39:54 by fnancy            #+#    #+#             */
/*   Updated: 2019/08/11 14:54:08 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		init_dir(t_nowdir **nowdir)
{
	(*nowdir)->file = NULL;
	(*nowdir)->m_fname = 0;
	(*nowdir)->total = 0;
	(*nowdir)->access = 1;
	(*nowdir)->c_files = 0;
	(*nowdir)->c_dirs = 0;
	(*nowdir)->l = NULL;
	(*nowdir)->m_blck_size = 0;
}

static void	cmp_dir_maxes(t_file *file, t_nowdir **nowdir)
{
	if (file->name_len > (*nowdir)->m_fname)
		(*nowdir)->m_fname = file->name_len;
	if (file->blck_size > (*nowdir)->m_blck_size)
		(*nowdir)->m_blck_size = file->blck_size;
}

static void	*return_dir_err(t_nowdir **nowdir)
{
	(*nowdir)->access = 0;
	return ((void *)1);
}

static void	*return_dir_err2(t_nowdir **nowdir, DIR *dir)
{
	(*nowdir)->access = -1;
	closedir(dir);
	return ((void *)1);
}

void		*create_nowdir(t_nowdir **nowdir, const char all, const char siz,\
							const char lon)
{
	DIR				*dir;
	struct dirent	*entry;
	t_file			*file;

	if (!err_open_dir((*nowdir)->name, &dir, all))
		return (return_dir_err(nowdir));
	init_dir(nowdir);
	while ((entry = readdir(dir)) != NULL)
	{
		(*nowdir)->c_files += 1;
		if (isdir(entry->d_type))
			(*nowdir)->c_dirs += 1;
		file = fill_file(entry->d_name, (*nowdir)->name, entry->d_namlen);
		if (siz && ((!all && file->name[0] != '.') || all) && !lon)
			(*nowdir)->total += file->st.st_blocks;
		if (file->access == 0)
			return (return_dir_err2(nowdir, dir));
		cmp_dir_maxes(file, nowdir);
		ft_dlstpush(&(*nowdir)->file, ft_dlstnew_cc((t_file *)file,\
					sizeof(t_file)));
	}
	closedir(dir);
	return ((void *)1);
}
