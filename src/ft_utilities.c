/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 22:23:16 by sconso            #+#    #+#             */
/*   Updated: 2014/03/26 21:16:20 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <ft_fc_str.h>
#include <stdlib.h>

void			ft_free_matrix(char ***matrix)
{
	int			i;

	i = -1;
	while ((*matrix)[++i])
	{
		free((*matrix)[i]);
		(*matrix)[i] = NULL;
	}
	free(*matrix);
	*matrix = NULL;
}

t_index			*ft_init_index(int i, int j, int k)
{
	t_index		*tmp;

	tmp = (t_index *)ft_malloc(sizeof(*tmp));
	tmp->i = i;
	tmp->j = j;
	tmp->k = k;
	return (tmp);
}

char			*ft_cstrtrim(char **str)
{
	char		*tmp;

	tmp = ft_strtrim(*str);
	free(*str);
	return (tmp);
}

char			*ft_cstrsub(char **str, unsigned int start, size_t len)
{
	char		*tmp;

	tmp = ft_strsub(*str, start, len);
	free(*str);
	return (tmp);
}

int				ft_strccmp(const char *s1, const char *s2, char c)
{
	if (!s1 || !s2)
		return (-2);
	while (*s1 && *s1 != c && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	if (*s1 == c)
		return (*(s1 - 1) - *(s2 - 1));
	return (*s1 - *s2);
}
