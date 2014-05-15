/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 12:03:30 by sconso            #+#    #+#             */
/*   Updated: 2014/03/27 16:55:38 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <ft_fc_print.h>
#include <ft_fc_str.h>
#include <stdlib.h>

static char		**ft_addenv(char ***env, char *add, int keys)
{
	char		**tmpenv;
	int			i;

	i = -1;
	tmpenv = (char **)ft_malloc(sizeof(char *) * (keys + 2));
	while ((*env)[++i])
		tmpenv[i] = ft_strdup((*env)[i]);
	tmpenv[i++] = ft_strdup(add);
	tmpenv[i] = 0;
	ft_free_matrix(env);
	return (tmpenv);
}

static void		ft_unsetenv_newenv(int nbkeys, int toremove, char ***env)
{
	char		**newenv;
	int			i;
	int			j;

	i = -1;
	j = -1;
	newenv = (char **)ft_malloc((nbkeys) * sizeof(char *));
	while ((*env)[++i])
	{
		if (i != toremove)
			newenv[++j] = ft_strdup((*env)[i]);
	}
	newenv[++j] = 0;
	ft_free_matrix(env);
	*env = newenv;
}

int				ft_env(char **cmd, char ***env)
{
	char		**tmp;
	t_env		senv;
	int			ret;

	if (!cmd || !cmd[0] || ft_strcmp(cmd[0], "env"))
		return (-1);
	if (cmd[1] && ft_strcmp(cmd[1], "-i"))
		return (ft_error("env : Illegal option\nUsage : env [-i]"));
	else if (cmd[1])
	{
		if (cmd[2])
		{
			senv.env = *env;
			senv.path = ft_get_path(*env);
			ret = ft_execve(&cmd[2], &senv);
			free(senv.path);
			return (ret);
		}
		return (0);
	}
	tmp = *env;
	while (*tmp)
		ft_putendl(*tmp++);
	return (0);
}

int				ft_setenv(char **cmd, char ***env)
{
	char		**newenv;
	int			nbkeys;
	int			i;

	if (!cmd || !cmd[0] || !cmd[1] || ft_strcmp(cmd[0], "setenv"))
		return (ft_error("Usage : setenv KEY=VALUE."));
	nbkeys = 0;
	i = -1;
	while ((*env)[++i])
	{
		if (ft_strccmp((*env)[i], cmd[1], '=') == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(cmd[1]);
			return (0);
		}
		++nbkeys;
	}
	newenv = ft_addenv(env, cmd[1], nbkeys);
	*env = newenv;
	return (0);
}

int				ft_unsetenv(char **cmd, char ***env)
{
	int			nbkeys;
	int			toremove;
	int			i;

	if (!cmd || !cmd[0] || !cmd[1] || ft_strcmp(cmd[0], "unsetenv"))
		return (ft_error("Usage : unsetenv KEY."));
	nbkeys = 0;
	i = -1;
	toremove = -1;
	while ((*env)[++i])
	{
		if (ft_strccmp((*env)[i], cmd[1], '=') == 0)
			toremove = nbkeys;
		++nbkeys;
	}
	if (toremove == -1)
		return (ft_error("Entry not found."));
	ft_unsetenv_newenv(nbkeys, toremove, env);
	return (0);
}
