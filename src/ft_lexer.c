/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 21:09:34 by sconso            #+#    #+#             */
/*   Updated: 2014/03/27 16:15:12 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <ft_fc_str.h>

static int			ft_lex(t_command *tmp, int apply, t_env *env)
{
	char			**cmd;
	int				ret;

	ft_test_redir(tmp);
	cmd = ft_strsplitarg(tmp->data);
	if (apply)
		ret = ft_execve(cmd, env);
	ft_reset_fd(env);
	ft_free_matrix(&cmd);
	return (ret);
}

static int			ft_lex_test(t_command *tmp, int ret)
{
	int				apply;

	apply = 0;
	if (tmp->type == AND && !ret)
		apply = 1;
	else if (tmp->type == OR && ret)
		apply = 1;
	else if (tmp->type == SEMICOL)
		apply = 1;
	return (apply);
}

static t_command	*ft_lex_pipe(int *apply, t_command *tmp)
{
	*apply = (tmp->prev ? 1 : 0);
	if (tmp->prev)
		tmp = ft_pipe(tmp->prev);
	else if (tmp->next)
		tmp = ft_pipe(tmp->next);
	return (tmp);
}

void				ft_lexer(t_list *lst, t_env *env)
{
	t_command		*tmp;
	int				apply;
	int				ret;

	ft_save_fd(env);
	tmp = lst->first;
	ret = 0;
	apply = 1;
	while (tmp)
	{
		if (tmp->type == CMD && (!tmp->next || tmp->next->type != PIPE))
			ret = ft_lex(tmp, apply, env);
		else if (tmp->type == PIPE)
		{
			if (!(tmp = ft_lex_pipe(&apply, tmp)))
				break ;
		}
		else
			apply = ft_lex_test(tmp, ret);
		tmp = tmp->next;
	}
}
