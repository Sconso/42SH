/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 11:34:01 by sconso            #+#    #+#             */
/*   Updated: 2014/03/27 15:20:55 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <ft_fc_str.h>
#include <stdlib.h>

char		**ft_cpy_env(char **env)
{
	char	**new;
	int		keys;
	int		i;

	if (!env || !*env)
		ft_exit("Environment Error : No environment found !");
	keys = 0;
	i = -1;
	while (env[++i])
		++keys;
	i = -1;
	new = (char **)ft_malloc((keys + 1) * sizeof(char *));
	while (env[++i])
		new[i] = ft_strdup(env[i]);
	new[i] = 0;
	return (new);
}

char		**ft_get_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 4))
		++i;
	if (!env[i])
		ft_exit("Environment Error : No path found !");
	path = ft_strsplit(env[i] + 5, ':');
	return (path);
}

char		*ft_get_key(char **env, char *key)
{
	while (*env)
	{
		if (!ft_strccmp(*env, key, '='))
			return (*(env) + ft_strlen(key) + 1);
		++env;
	}
	return (NULL);
}
