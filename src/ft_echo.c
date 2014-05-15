/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggarrigu <ggarrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 15:21:57 by ggarrigu          #+#    #+#             */
/*   Updated: 2014/03/27 19:07:55 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <ft_fc_str.h>
#include <ft_fc_print.h>
#include <stdlib.h>

char		*ft_echo_parse(char **str)
{
	char	*tmp;
	char	*ret;
	int		i;

	if (!str || !str[0] || !str[1])
		return (NULL);
	tmp = ft_strdup("\0");
	i = (str[1] && !ft_strcmp(str[1], "-n") ? 1 : 0);
	while (str[++i])
		tmp = ft_strcleanjoin(tmp, str[i]);
	ret = ft_strtrim(tmp);
	free(tmp);
	return (ret);
}

char		*ft_echo_quote(char *str)
{
	char	*quote;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(str);
	if (str[0] == '"' || str[0] == '\'')
	{
		quote = (char *)ft_malloc(sizeof(char) * (len - 1));
		i = 0;
		j = -1;
		while (str[++i] && i < (len - 1))
			quote[++j] = str[i];
		quote[++j] = '\0';
	}
	else
	{
		quote = (char *)ft_malloc(sizeof(char) * len + 1);
		i = -1;
		while (str[++i])
			quote[i] = str[i];
		quote[i] = '\0';
	}
	return (quote);
}

int			ft_echo(char **cmd, char ***env)
{
	char	*tmp;
	char	*quote;

	(void)env;
	if (!cmd[1])
	{
		ft_putchar('\n');
		return (0);
	}
	tmp = ft_echo_parse(cmd);
	quote = ft_echo_quote(tmp);
	if (tmp)
		free(tmp);
	if (!ft_strcmp(cmd[1], "-n"))
		ft_putstr(quote);
	else if (ft_strcmp(cmd[1], "-n"))
		ft_putendl(quote);
	free(quote);
	return (0);
}
