/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:12:21 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/08/11 16:32:58 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <pwd.h>
# include <time.h>
# include <sys/ioctl.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <limits.h>
# include <grp.h>
# include "libft.h"

struct winsize		term;

/*
** nsr -f не сортировать, отобразить файлы в том порядке в котором они \
**		записаны на диск
** rev -r отобразить в обратном порядке
** dir -d выдавать имена каталогов как будто они обычные файлы в \
**		место того что бы показывать их содержимое
** col -C вывод по колонкам
** rec -R рекурсивный обход каталогов
** tim -t сортировка по времени последнего изменения
** tds -u сортировать по врмени последнего доступа к файлу
** all -a вывод со скрытыми файлами
** one -1 вывод по 1 элементу на строку
** ngu -g не показывать группу и пользователя при  длинном выводе
** ngw -G не показывать инфо о группе при длинном выводе
** lon -l подробный вывод
** siz -s выводить размер блока рядом
*/
struct winsize		term;

typedef struct		s_format
{
	char			rec;
	char			tim;
	char			rev;
	char			lon;
	char			all;
	char			nsr;
	char			tds;
	char			dir;
	char			ngu;
	char			ngw;
	char			siz;
	char			sra;
	char			pcz;
	char			col;
	char			one;
	char			argc;
}					t_format;

typedef	struct		s_mcol
{
	int				colcount;
	int				rast;
	int				rowcount;
	int				size;
}					t_mcol;

/*
** длина блоков
*/
typedef struct		s_len
{
	__uint32_t		link;
	__uint32_t		user;
	__uint32_t		grou;
	__uint32_t		size;
	__uint32_t		blck;
}					t_len;

typedef struct		s_time
{
	char			timef[16];
	long			atime;
	long			mtime;
	long			ctime;
}					t_timef;

/*
** sysf - системный ли файл
** rights - права доступа
** links - количество ссылок
** timef - время файла
** block - блоки памяти
*/
typedef struct		s_detail
{
	char			error;
	char			sysf;
	size_t			total;
	char			rights[13];
	char			*user;
	char			*group;
	blkcnt_t		block;
	t_timef			timef;
	unsigned int	major;
	unsigned int	minor;
	t_len			*l;
}					t_detail;

/*
** name - имя файла
** type - тип файла
** timef - время файла
** access - доступ
*/
typedef struct		s_file
{
	char			*name;
	char			*f_path;
	__uint16_t		name_len;
	__uint32_t		blck_size;
	char			type;
	char			access;
	struct stat		st;
	t_detail		*det;
}					t_file;

typedef struct		s_nowdir
{
	t_len			*l;
	char			access;
	unsigned int	c_dirs;
	unsigned int	c_files;
	__uint32_t		m_fname;
	__uint32_t		m_blck_size;
	char			*name;
	t_dlist			*file;
	blkcnt_t		total;
}					t_nowdir;

void				ft_ls(void);
char				get_type_d(const mode_t st_mode);
int					parser(int argc, char **argv, t_format *f);
t_detail			*get_data_file(const char *dir_name,\
								const struct stat st);
void				get_data_l(t_nowdir **ndir, const char all);
void				sort(t_dlist **list, const t_format f);
char				isdir(const __uint8_t d_type);
void				do_recursion(const t_format f, t_nowdir *dir);
void				do_flags(const t_format f, t_nowdir *dir);
void				*create_nowdir(t_nowdir **nowdir,\
							const char all, const char siz, const char lon);
void				free_dir(t_nowdir **dir);
void				free_file(t_file **file);
void				free_details(t_detail **det);
void				formatter(const t_file *file,\
								const t_format f, const t_len *l);
__uint32_t			get_block(const __uint32_t st_size);
void				put_mcol(const t_format f, t_nowdir *dir);
void				free_double_dlist(t_dlist ***dlist);
t_file				*fill_file(const char *d_name, const char *n_dir_name,\
								const int ent_lendname);
void				create_d_flag(char **argv, int n,\
									int argc, t_nowdir **nowdir);
void				help_put_time(const t_file *fi, char tds);
void				put_time(const char *ctimef,\
						const long mtime, const long atime, const long c_time);
void				init_dir(t_nowdir **nowdir);
void				put_l(const t_format f, t_nowdir *dir);
void				put_one(const t_format f, t_nowdir *dir);
char				err_open_dir(const char *path, DIR **dir, const char all);
#endif
