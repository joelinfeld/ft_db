/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 12:07:17 by biremong          #+#    #+#             */
/*   Updated: 2017/01/17 18:16:05 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		match_fd(void *data_ref, void *strct)
{
	if (((t_fds*)strct)->fd == *(int*)data_ref)
		return (0);
	return (1);
}

void	save_leftover_data(t_list **head, char *nl_pnt, int fd, int extra_len)
{
	t_fds	fds;
	t_list	*fd_link;

	if (*head && (fd_link = ft_list_find(*head, &fd, match_fd)))
	{
		((t_fds*)fd_link->content)->str = ft_str_resize(\
			((t_fds*)fd_link->content)->str,\
			ft_strlen(((t_fds*)fd_link->content)->str) + extra_len);
		ft_strncat(((t_fds*)fd_link->content)->str, nl_pnt + 1, extra_len);
	}
	else
	{
		fds = (t_fds) {fd, ft_strndup(nl_pnt + 1, extra_len)};
		ft_lstadd(head, ft_lstnew(&fds, sizeof(fds)));
	}
}

int		check_list_for_old_dirty_data(t_list **head, int fd, char **line)
{
	t_list	*fd_link;
	char	*nl_pnt;

	if (!*head || !(fd_link = ft_list_find(*head, &fd, match_fd)))
		return (0);
	if ((nl_pnt = ft_strchr(((t_fds*)fd_link->content)->str, '\n')))
	{
		*nl_pnt = '\0';
		*line = ft_strdup(((t_fds*)fd_link->content)->str);
		nl_pnt = ft_strdup(nl_pnt + 1);
		free(((t_fds*)fd_link->content)->str);
		((t_fds*)fd_link->content)->str = nl_pnt;
		if (!*nl_pnt)
		{
			free(((t_fds*)fd_link->content)->str);
			ft_list_remove_if(head, &fd, match_fd);
		}
		return (1);
	}
	*line = ft_strdup(((t_fds*)fd_link->content)->str);
	free(((t_fds*)fd_link->content)->str);
	ft_list_remove_if(head, &fd, match_fd);
	return (0);
}

int		read_some_stuff(t_list **head, int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE];
	char		*nl_pnt;
	int			extra_len;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		*line = *line ? \
			ft_str_resize(*line, ft_strlen(*line) + ret) : ft_strnew(ret);
		if ((nl_pnt = ft_memchr(buf, '\n', ret)))
		{
			*nl_pnt = '\0';
			extra_len = ret - ft_strlen(buf) - 1;
			if (nl_pnt != buf + ret - 1)
				save_leftover_data(head, nl_pnt, fd, extra_len);
		}
		ft_strncat(*line, buf, ret);
		if (nl_pnt)
			break ;
	}
	return (*line ? 1 : 0);
}

int		ft_gnl(const int fd, char **line)
{
	static t_list	*head = NULL;

	if (!line)
		return (-1);
	*line = NULL;
	if (check_list_for_old_dirty_data(&head, fd, line))
		return (1);
	return (read_some_stuff(&head, fd, line));
}
