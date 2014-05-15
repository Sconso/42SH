/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:57:56 by sconso            #+#    #+#             */
/*   Updated: 2014/03/26 19:04:51 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_fc_print.h>
#include <ft_fc_str.h>
#include <get_next_line.h>
#include <stdlib.h>

int			ft_is_quote(char c)
{
	if (c == '\'' || c == '"' || c == '`')
		return (1);
	return (0);
}

char		**ft_ask_quote(char quote, char **command)
{
	char	*add;

	if (quote == '\'')
		ft_putstr("Squote > ");
	else if (quote == '"')
		ft_putstr("Dquote > ");
	else if (quote == '`')
		ft_putstr("Bquote > ");
	add = get_next_line(0);
	*command = ft_strcleanjoin(*command, add);
	free(add);
	return (command);
}

int			ft_quotes(int *i, char *command)
{
	char	quote;
	int		j;

	j = *i;
	quote = command[j];
	while (command[++j])
	{
		if (command[j] == quote && command[j - 1] != '\\')
		{
			*i = j + 1;
			return (*i);
		}
	}
	return (-1);
}
