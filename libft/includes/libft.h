/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 10:23:42 by biremong          #+#    #+#             */
/*   Updated: 2017/05/05 18:32:32 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUFF_SIZE 80

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_fds
{
	int		fd;
	char	*str;
}				t_fds;

int				ft_atoi(const char *str);
intmax_t		ft_atoimax(const char *str);
int				ft_atoi_base(int base, char *str);
void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *str, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *str);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *str);
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *str, int c);
char			*ft_strstr(const char *big, const char *little);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_itoa(intmax_t n);
char			*ft_itoa_base(uintmax_t n, int base, int upper_flag);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
void			ft_strclr(char *s);
void			ft_strdel(char **as);
int				ft_strequ(char const *s1, char const *s2);
void			ft_striter(char *s, void (*f)(char*));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_strsplit(char const *s, char c);
char			*ft_strtrim(char const *s);
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(void const *content, size_t content_size);
t_list			*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)());
int				ft_lstlen(t_list *head);
char			*ft_str_resize(char *str, size_t len);
void			ft_list_remove_if\
					(t_list **begin_list, void *data_ref, int (*cmp)());
char			*ft_strndup(char *str, size_t len);
int				ft_gnl(int fd, char **line);
int				ft_arrlen2(char **arr);
int				ft_arrlen3(char ***arr);
void			ft_arrdel2(char **arr);
void			ft_arrdel3(char ***arr);
void			ft_crash(void);
void			ft_error(void);
int				ft_open(char *file_name);
int				ft_read(int fd, char *buf, int len);
void			ft_close(int fd);
int				ft_isupper(char c);
int				ft_islower(char c);
long long		ft_power(int base, unsigned int exp);
int				ft_printf(const char *format, ...);
void			*ft_malloc(size_t bytes);
void			ft_str_tolower(char **str);
double			ft_atof(char *str);

#endif
