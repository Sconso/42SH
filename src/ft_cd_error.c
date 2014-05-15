/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:52:50 by sconso            #+#    #+#             */
/*   Updated: 2014/03/27 19:03:37 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <unistd.h>
#include <sys/stat.h>

int					ft_chdir(char *path)
{
	struct stat		st_buf;

	if (!path)
		return (-1);
	if (access(path, F_OK) == -1)
		return (ft_error("Folder doesn't exist."));
	if (stat(path, &st_buf))
		return (ft_error("Unknown error."));
	if (S_ISREG(st_buf.st_mode))
		return (ft_error("Not a directory."));
	if (access(path, X_OK) == -1)
		return (ft_error("Access denied : Don't have requiered permissions."));
	if (chdir(path) == -1)
		return (ft_error("Unknown error."));
	return (0);
}
