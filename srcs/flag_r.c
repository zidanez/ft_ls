/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:14:11 by fnancy            #+#    #+#             */
/*   Updated: 2019/08/11 14:54:37 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_nowdir		*init_new_dir(t_format f, t_file *file)
{
	t_nowdir		*new_dir;

	if (!(new_dir = (t_nowdir *)malloc(sizeof(t_nowdir))))
		exit(0);
	new_dir->name = ft_strdup(file->f_path);
	create_nowdir(&new_dir, f.all, f.siz, f.lon);
	return (new_dir);
}

static void			print_name_dir(t_nowdir *new_dir)
{
	if (new_dir->name[0] == '/' && new_dir->name[1] == '/')
		ft_printf("\n%s:\n", new_dir->name + 1);
	else
		ft_printf("\n%s:\n", new_dir->name);
}

void				do_recursion(const t_format f, t_nowdir *dir)
{
	t_dlist		*start;
	t_nowdir	*new_dir;
	t_file		*file;

	start = dir->file;
	while (start)
	{
		file = (t_file *)start->content;
		if (file->type == 'd' && file->access &&\
			ft_strcmp(file->name, ".") != 0 && ft_strcmp(file->name, "..") != 0)
		{
			if (!f.all && file->name[0] == '.')
			{
				start = start->next;
				continue ;
			}
			new_dir = init_new_dir(f, file);
			print_name_dir(new_dir);
			if (new_dir->access)
				do_flags(f, new_dir);
			free_dir(&new_dir);
			new_dir = NULL;
		}
		start = start->next;
	}
}
