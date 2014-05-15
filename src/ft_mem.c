/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 22:18:15 by sconso            #+#    #+#             */
/*   Updated: 2014/03/19 20:35:40 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <stdlib.h>

void		*ft_malloc(long size)
{
	int		i;
	void	*tmp;

	i = -1;
	while (++i < 100)
	{
		if ((tmp = malloc(size)) != 0)
			return (tmp);
	}
	ft_exit("Memory error : You dont have enough memory :(.\n");
	return (0);
}
