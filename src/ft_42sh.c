/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 22:00:45 by sconso            #+#    #+#             */
/*   Updated: 2014/03/27 19:06:56 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <ft_fc_print.h>
#include <ft_fc_str.h>
#include <get_next_line.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void				ft_welcome(void)
{
	ft_putstr("\033[2J\033[H");
	ft_putstr("========================================");
	ft_putstr("========================================\n");
	ft_putendl("\t\t_   ___  _______  _______  __   __");
	ft_putendl("\t\t| | |   ||       ||       ||  | |  |");
	ft_putendl("\t\t| |_|   ||____   ||  _____||  |_|  |");
	ft_putendl("\t\t|       | ____|  || |_____ |       |");
	ft_putendl("\t\t|___    || ______||_____  ||       |");
	ft_putendl("\t\t    |   || |_____  _____| ||   _   |");
	ft_putendl("\t\t    |___||_______||_______||__| |__|");
	ft_putstr("========================================");
	ft_putstr("========================================\n\n");
}

int					main(void)
{
	extern char		**environ;
	char			*command;
	t_env			*env;
	t_list			*lst;

	ft_signals();
	ft_welcome();
	env = (t_env *)ft_malloc(sizeof(*env));
	env->env = ft_cpy_env(environ);
	env->path = ft_get_path(env->env);
	while (ft_putstr(INVIT) && (command = get_next_line(0)))
	{
		if (!ft_strcmp(command, "exit"))
			break ;
		ft_parsing(&command, (lst = ft_newlist()));
		if (lst && lst->first)
			ft_lexer(lst, env);
		ft_free_list(&lst);
		free(command);
	}
	if (command)
		free(command);
	return (0);
}
