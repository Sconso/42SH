/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggarrigu <ggarrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 17:53:29 by ggarrigu          #+#    #+#             */
/*   Updated: 2014/03/27 19:05:45 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <ft_fc_str.h>
#include <ft_fc_print.h>
#include <unistd.h>
#include <stdlib.h>

static char		*ft_get_cwd(void)
{
	char		*cwd;
	int			size;

	size = 2;
	cwd = (char *)ft_malloc(sizeof(char) * size);
	if ((getcwd(cwd, size)) == NULL)
	{
		while ((getcwd(cwd, size)) == NULL)
		{
			free(cwd);
			cwd = NULL;
			size = size * 2;
			cwd = (char *)ft_malloc(sizeof(char) * size);
		}
	}
	return (cwd);
}

static int		ft_change_env(char **env)
{
	char		**tmp;
	char		*cwd;

	tmp = (char **)ft_malloc(3 * sizeof(char *));
	tmp[2] = NULL;
	tmp[0] = ft_strdup("setenv");
	tmp[1] = ft_strjoin("OLDPWD=", ft_get_key(env, "PWD"));
	ft_setenv(tmp, &env);
	free(tmp[1]);
	cwd = ft_get_cwd();
	tmp[1] = ft_strjoin("PWD=", cwd);
	ft_setenv(tmp, &env);
	ft_free_matrix(&tmp);
	free(cwd);
	return (1);
}

static int		ft_cd_home(char **env, char *dir)
{
	char		*home;
	int			ret;

	ret = 0;
	if ((home = ft_get_key(env, "HOME")) == NULL)
		return (ft_error("Set HOME with setenv command before."));
	if (dir == NULL || dir[0] == 0 || (dir[0] == '~' && dir[1] == 0))
		chdir(home);
	else if (dir[0] == '~' && dir[1] == '/')
	{
		home = ft_strjoin(ft_get_key(env, "HOME"), (dir + 1));
		ret = ft_chdir(home);
		free(home);
	}
	else
		return (-1);
	ft_change_env(env);
	return (ret);
}

static int		ft_cd_prev(char **env, char *dir)
{
	char		*oldpwd;
	char		*pwd;
	int			ret;

	if ((oldpwd = ft_get_key(env, "OLDPWD")) == NULL)
		return (ft_error("Set OLDPWD with setenv command before."));
	if ((pwd = ft_get_key(env, "PWD")) == NULL)
		return (ft_error("Set PWD with setenv command before."));
	ret = 0;
	if (dir[0] == '-' && dir[1] == 0)
	{
		ret = ft_chdir(oldpwd);
		ft_putendl(oldpwd);
	}
	else if (dir[0] == '-')
	{
		pwd = ft_strjoin(ft_get_key(env, "HOME"), (dir + 1));
		ret = ft_chdir(pwd);
		free(pwd);
	}
	ft_change_env(env);
	return (ret);
}

int				ft_cd(char **cmd, char ***env)
{
	char		*cwd;
	int			ret;

	ret = 0;
	if (!cmd || !cmd[0] || (cmd[1] && cmd[2]))
		return (ft_error("Usage : cd [dir]"));
	if (!cmd[1] || cmd[1][0] == '~')
		ret = ft_cd_home(*env, cmd[1]);
	else if (cmd[1] && cmd[1][0] == '-')
		ret = ft_cd_prev(*env, cmd[1]);
	else if (cmd[1])
	{
		ret = ft_chdir(cmd[1]);
		cwd = ft_get_cwd();
		ft_change_env(*env);
		free(cwd);
	}
	return (ret);
}
