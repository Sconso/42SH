/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 21:22:15 by sconso            #+#    #+#             */
/*   Updated: 2014/03/27 19:09:28 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <ft_fc_str.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

static t_builtins		*ft_s_builtins(void)
{
	static t_builtins	*builtins = NULL;

	if (!builtins)
	{
		builtins = (t_builtins *)ft_malloc(6 * sizeof(*builtins));
		builtins[0].name = ft_strdup("cd");
		builtins[1].name = ft_strdup("echo");
		builtins[2].name = ft_strdup("exit");
		builtins[3].name = ft_strdup("env");
		builtins[4].name = ft_strdup("setenv");
		builtins[5].name = ft_strdup("unsetenv");
		builtins[0].func = &ft_cd;
		builtins[1].func = &ft_echo;
		builtins[2].func = NULL;
		builtins[3].func = &ft_env;
		builtins[4].func = &ft_setenv;
		builtins[5].func = &ft_unsetenv;
	}
	return (builtins);
}

int						ft_exec_builtin(char **cmd, char ***env)
{
	int					i;
	int					ret;
	t_builtins			*builtins;

	builtins = ft_s_builtins();
	i = -1;
	ret = -5;
	while (++i < 6)
	{
		if (!ft_strcmp(cmd[0], builtins[i].name))
		{
			if (builtins[i].func != NULL)
			{
				ret = builtins[i].func(cmd, env);
				printf("[%d]\n", ret);
			}
			break ;
		}
	}
	return (ret);
}

int						ft_execve(char **cmd, t_env *env)
{
	pid_t				pid;
	char				*tmp;
	int					i;

	if ((i = ft_exec_builtin(cmd, &(env->env))) != -5)
		return (i);
	i = -1;
	if (!(pid = fork()))
	{
		execve(cmd[0], &cmd[0], env->env);
		while (env->path[++i])
		{
			tmp = ft_strjoin(env->path[i], "/");
			tmp = ft_strcleanjoin(tmp, cmd[0]);
			execve(tmp, &cmd[0], env->env);
			free(tmp);
		}
		ft_error("Command not found !");
		exit(EXIT_FAILURE);
	}
	else if (pid != -1)
		waitpid(pid, &i, WUNTRACED);
	else
		return (ft_error("Can't fork."));
	return (i);
}
