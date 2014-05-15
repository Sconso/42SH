/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/10 22:10:25 by sconso            #+#    #+#             */
/*   Updated: 2014/03/27 15:59:26 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_fc_print.h>
#include <unistd.h>

int			ft_assert(int test)
{
	if (test)
		return (0);
	return (-1);
}

int			ft_error(char *str)
{
	ft_putstr_fd("\033[1;31mERROR : ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("\033[0m", 2);
	return (-1);
}

void		ft_exit(char *str)
{
	ft_putstr_fd("\033[1;31mERROR : ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("\033[0m", 2);
	_exit(0);
}

int			ft_line_error(char *str, char *line)
{
	ft_putstr_fd("\033[1;31m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" near \"\033[1;33m", 2);
	ft_putstr_fd(line, 2);
	ft_putendl_fd("\033[1;31m\"\033[0m", 2);
	return (-1);
}

int			ft_file_error(char *file, char *error)
{
	ft_putstr_fd("\033[1;31mError on file \"", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("\": ", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd("\033[0m", 2);
	return (-1);
}
