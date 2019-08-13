/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:14:11 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/08/11 17:42:38 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*fill_file(const char *d_name, const char *n_dir_name,\
						int ent_lendname)
{
	struct stat		st;
	t_file			*file;

	if (!(file = (t_file *)malloc(sizeof(t_file))))
		exit(0);
	if (ft_strcmp(n_dir_name, "") != 0)
		file->f_path = ft_concat(2, "1/", n_dir_name, d_name);
	else
		file->f_path = ft_strdup(d_name);
	file->name = ft_strdup(d_name);
	file->det = NULL;
	if (lstat(file->f_path, &st) == -1)
	{
		file->access = 0;
		return (file);
	}
	file->st = st;
	file->access = 1;
	file->type = get_type_d(st.st_mode);
	file->name_len = ent_lendname;
	file->blck_size = ft_nbrlen((int)file->st.st_blocks);
	return (file);
}

char		err_open_dir(const char *path, DIR **dir, const char all)
{
	char	*name;
	char	*n2;

	(*dir) = opendir(path);
	n2 = NULL;
	if (!(*dir))
	{
		name = ft_strrchr(path, '/');
		if (name && all)
			n2 = ft_concat(3, "00", "ft_ls: ", ++name, ":");
		else if (!all && name && name[1] != '.')
			n2 = ft_concat(3, "00", "ft_ls: ", ++name, ":");
		else if (!name && all)
			n2 = ft_concat(3, "00", "ft_ls: ", path, ":");
		else if (!name && !all && path[0] != '.')
			n2 = ft_concat(3, "00", "ft_ls: ", path, ":");
		if (n2)
		{
			perror(n2);
			free(n2);
		}
		return (0);
	}
	return (1);
}

void		do_flags(const t_format f, t_nowdir *dir)
{
	sort(&dir->file, f);
	if (f.lon && dir->access != 0 && dir->access != -1)
		put_l(f, dir);
	else if (f.one && dir->access)
		put_one(f, dir);
	else if ((f.col && dir->access != 0 && dir->access != -1))
		put_mcol(f, dir);
	if (f.rec && dir->access && !f.dir)
		do_recursion(f, dir);
}

static void	help_main(int n, char **argv, int argc, t_format f)
{
	char		fl;
	t_nowdir	*nowdir;

	fl = 0;
	while (n < argc)
	{
		nowdir = (t_nowdir *)malloc(sizeof(t_nowdir));
		nowdir->name = ft_strdup(argv[n]);
		create_nowdir(&nowdir, f.all, f.siz, f.lon);
		if (fl)
			ft_printf("\n");
		if (f.argc)
			ft_printf("%s:\n", nowdir->name);
		if (nowdir->access)
			do_flags(f, nowdir);
		fl = 1;
		n++;
		free_dir(&nowdir);
	}
}

int			main(int argc, char **argv)
{
	t_format	f;
	t_nowdir	*nowdir;
	int			n;

	n = parser(argc, argv, &f);
	ioctl(0, TIOCGWINSZ, &term);
	if ((argc == 1 && argc++) || (n == argc && n--))
		argv[n] = ".";
	if (n != argc - 1)
		f.argc = 1;
	if (f.dir)
	{
		nowdir = (t_nowdir *)malloc(sizeof(t_nowdir));
		create_d_flag(argv, n, argc, &nowdir);
		if (nowdir->access)
			do_flags(f, nowdir);
		free_dir(&nowdir);
	}
	else
		help_main(n, argv, argc, f);
	return (1);
}
