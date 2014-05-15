/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 19:05:36 by sconso            #+#    #+#             */
/*   Updated: 2014/03/26 19:06:57 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <unistd.h>

void			ft_save_fd(t_env *env)
{
	env->in = dup(0);
	env->out = dup(1);
}

void			ft_reset_fd(t_env *env)
{
	dup2(env->in, STDIN_FILENO);
	dup2(env->out, STDOUT_FILENO);
}
