/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 19:07:21 by sconso            #+#    #+#             */
/*   Updated: 2014/03/26 21:19:14 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <fcntl.h>
#include <unistd.h>

void			ft_test_redir(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == SIN && tmp->next && tmp->next->type == CMD)
			ft_change_in(tmp->next->data, 0);
		else if (tmp->type == DIN && tmp->next && tmp->next->type == CMD)
			ft_change_in(tmp->next->data, 1);
		else if (tmp->type == SOUT && tmp->next && tmp->next->type == CMD)
			ft_change_out(tmp->next->data, 0);
		else if (tmp->type == DOUT && tmp->next && tmp->next->type == CMD)
			ft_change_out(tmp->next->data, 1);
		else if (tmp->type != CMD)
			return ;
		tmp = tmp->next;
	}
}

int				ft_change_in(char *file, int app)
{
	int			fd;

	if (!app)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY);
	if (fd == -1)
	{
		if (access(file, R_OK))
			return (ft_file_error(file, "Permission Denied."));
		return (ft_file_error(file, "File doesnt exist."));
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int				ft_change_out(char *file, int app)
{
	int			fd;

	if (!app)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, \
					S_IRWXU | S_IRGRP | S_IROTH);
	else
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, \
					S_IRWXU | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		if (access(file, R_OK))
			return (ft_file_error(file, "Permission Denied."));
		return (ft_file_error(file, "Unknown Error."));
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}
