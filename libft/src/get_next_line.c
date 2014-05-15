/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/02 19:12:10 by sconso            #+#    #+#             */
/*   Updated: 2014/03/26 19:21:03 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include <ft_fc_str.h>
#include <stdlib.h>
#include <unistd.h>

static char			*ft_exit(char **str)
{
	free(*str);
	*str = 0;
	return (0);
}

static char			*ft_read(char **buf, char **tmp, int fd)
{
	char			*size;
	int				ret;

	if ((size = ft_strchr(*tmp, '\n')))
		return (size);
	while ((ret = read(fd, *buf, BUFF_SIZE)))
	{
		(*buf)[ret] = 0;
		*tmp = ft_strcleanjoin(*tmp, *buf);
		if ((size = ft_strchr(*tmp, '\n')))
			return (size);
	}
	return (size);
}

char				*get_next_line(int const fd)
{
	static char		*tmp = 0;
	char			*buf;
	char			*size;

	if (fd < 0 || BUFF_SIZE < 1)
		return (ft_exit(&tmp));
	tmp = (tmp ? tmp : ft_strdup(""));
	buf = ft_strnew(BUFF_SIZE + 1);
	if (!buf)
		return (ft_exit(&tmp));
	size = ft_read(&buf, &tmp, fd);
	free(buf);
	if (tmp[0] && (size || (size = ft_strrchr(tmp, 0))))
	{
		buf = ft_strsub(tmp, 0, size - tmp);
		free(tmp);
		tmp = (size[0] ? ft_strdup(size + 1) : ft_strdup(""));
		return (buf);
	}
	return (ft_exit(&tmp));
}
