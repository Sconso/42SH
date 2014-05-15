/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 19:33:16 by sconso            #+#    #+#             */
/*   Updated: 2014/03/26 19:35:50 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <ft_fc_str.h>

char		ft_istoken(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>')
		return (c);
	return (0);
}

int			ft_test_token(char *tmp)
{
	int		type;

	if (!*tmp)
		return (-1);
	else if (!ft_strcmp(tmp, ";"))
		type = SEMICOL;
	else if (!ft_strcmp(tmp, "&&"))
		type = AND;
	else if (!ft_strcmp(tmp, "||"))
		type = OR;
	else if (!ft_strcmp(tmp, "|"))
		type = PIPE;
	else if (!ft_strcmp(tmp, "<"))
		type = SIN;
	else if (!ft_strcmp(tmp, "<<"))
		type = DIN;
	else if (!ft_strcmp(tmp, ">"))
		type = SOUT;
	else if (!ft_strcmp(tmp, ">>"))
		type = DOUT;
	else
		type = CMD;
	return (type);
}

void		ft_add_token(char *command, int i, int j, t_list *lst)
{
	char	*tmp;
	int		type;

	tmp = ft_strsub(command, j, i - j);
	tmp = ft_cstrtrim(&tmp);
	type = ft_test_token(tmp);
	if (type >= 0)
		ft_pushlast(lst, tmp, type);
}
