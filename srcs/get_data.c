/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:38:49 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/08/11 13:47:30 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			get_type_d(const mode_t st_mode)
{
	if (S_ISREG(st_mode) == 1)
		return ('-');
	else if (S_ISDIR(st_mode) == 1)
		return ('d');
	else if (S_ISLNK(st_mode) == 1)
		return ('l');
	else if (S_ISCHR(st_mode) == 1)
		return ('c');
	else if (S_ISSOCK(st_mode) == 1)
		return ('s');
	else if (S_ISFIFO(st_mode) == 1)
		return ('m');
	return ('b');
}

static char		get_file_acl(const char *path)
{
	acl_t	tmp;
	char	buf[101];

	if (listxattr(path, buf, sizeof(buf), XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((tmp = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
	{
		acl_free(tmp);
		return ('+');
	}
	return (' ');
}

static void		get_right(const mode_t st_mode, char *right, const char *path)
{
	right[0] = get_type_d(st_mode);
	right[1] = st_mode & S_IRUSR ? 'r' : '-';
	right[2] = st_mode & S_IWUSR ? 'w' : '-';
	right[3] = st_mode & S_IXUSR ? 'x' : '-';
	right[4] = st_mode & S_IRGRP ? 'r' : '-';
	right[5] = st_mode & S_IWGRP ? 'w' : '-';
	right[6] = st_mode & S_IXGRP ? 'x' : '-';
	right[7] = st_mode & S_IROTH ? 'r' : '-';
	right[8] = st_mode & S_IWOTH ? 'w' : '-';
	right[9] = st_mode & S_IXOTH ? 'x' : '-';
	right[10] = get_file_acl(path);
	right[11] = '\0';
}

t_detail		*get_data_file(const char *dir_name, struct stat st)
{
	t_detail	*det;

	if (!(det = (t_detail*)malloc(sizeof(t_detail))))
		exit(1);
	get_right(st.st_mode, det->rights, dir_name);
	if (det->rights[0] != '<')
	{
		det->user = getpwuid(st.st_uid)->pw_name;
		det->group = getgrgid(st.st_gid)->gr_name;
		det->block = st.st_blocks;
		det->sysf = det->rights[0] == 'c' || det->rights[0] == 'b' ? 1 : 0;
		det->minor = det->sysf ? minor(st.st_rdev) : 0;
		det->major = det->sysf ? major(st.st_rdev) : 0;
	}
	return (det);
}
