/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 23:01:18 by sconso            #+#    #+#             */
/*   Updated: 2014/03/26 19:56:26 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <ft_fc_str.h>

static int		ft_separator(char tok, char **cmd, t_index *index, t_list *lst)
{
	int			i;
	int			j;

	i = index->i;
	j = index->j;
	if ((tok != ';' && tok != 0) && (*cmd)[i + 1] == tok)
		i += 2;
	else if (ft_istoken((*cmd)[i + 1]))
		return (ft_line_error("Parsing Error", &(*cmd)[i - j]));
	else
		i++;
	if (ft_istoken((*cmd)[i]))
		return (ft_line_error("Parsing Error", &(*cmd)[i - j]));
	if (lst->last && lst->last->type != CMD)
		return (ft_line_error("Parsing Error", &(*cmd)[i - j]));
	ft_add_token(*cmd, i, j, lst);
	j = i;
	index->i = i;
	index->j = j;
	return (1);
}

int				ft_parsing(char **cmd, t_list *lst)
{
	char		tok;
	t_index		*index;

	index = ft_init_index(0, 0, 0);
	while ((*cmd)[index->i])
	{
		while ((*cmd)[index->i] && !(tok = ft_istoken((*cmd)[index->i])))
		{
			if (ft_is_quote((*cmd)[index->i]))
			{
				if (ft_quotes(&(index->i), *cmd) == -1)
					cmd = ft_ask_quote((*cmd)[index->i], cmd);
			}
			else
				index->i++;
		}
		if (index->i != 0 && index->j != index->i)
		{
			ft_add_token(*cmd, index->i, index->j, lst);
			index->j = index->i;
		}
		if ((*cmd)[index->i])
			ft_separator(tok, cmd, index, lst);
	}
	return (1);
}
