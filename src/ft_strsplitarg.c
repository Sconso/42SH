/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitarg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:52:07 by sconso            #+#    #+#             */
/*   Updated: 2014/03/26 18:53:21 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_fc_mem.h>
#include <stdlib.h>

static char		**ft_malloc_words(char const *s)
{
	char	**str;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
		{
			size++;
			while (s[i] && s[i] != ' ' && s[i] != '\t')
				i++;
		}
		else
			i++;
	}
	str = (char **)malloc((size + 1) * sizeof(str));
	if (str == 0)
		return (0);
	str[size] = 0;
	return (str);
}

static void		ft_malloc_letters(char const *s, char **str)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
		{
			size = 0;
			while (s[i] && s[i] != ' ' && s[i] != '\t')
			{
				size++;
				i++;
			}
			str[j] = (char *)malloc((size + 1) * sizeof(*str));
			if (str[j] == 0)
				return ;
			ft_bzero(str[j], size);
			j++;
		}
		else
			i++;
	}
}

char			**ft_strsplitarg(char const *s)
{
	int		size;
	int		i;
	int		j;
	char	**str;

	size = 0;
	i = 0;
	if (s == 0)
		return (0);
	str = ft_malloc_words(s);
	ft_malloc_letters(s, str);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
		{
			j = 0;
			while (s[i] && s[i] != ' ' && s[i] != '\t')
				str[size][j++] = s[i++];
			str[size][j] = 0;
			size++;
		}
		else
			i++;
	}
	return (str);
}
