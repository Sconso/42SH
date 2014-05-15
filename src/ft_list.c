/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 20:21:15 by sconso            #+#    #+#             */
/*   Updated: 2014/03/25 13:11:59 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_42sh.h>
#include <ft_fc_print.h>
#include <stdlib.h>

t_list			*ft_newlist(void)
{
	t_list		*list;

	list = (t_list *)ft_malloc(sizeof(*list));
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
	return (list);
}

t_command		*ft_pushfirst(t_list *list, char *data, int type)
{
	t_command	*new;

	if (!list || !data)
		return (NULL);
	new = (t_command *)ft_malloc(sizeof(*new));
	new->data = data;
	new->type = type;
	new->next = list->first;
	new->prev = NULL;
	if (!list->first)
		list->last = new;
	else
		list->first->prev = new;
	list->first = new;
	list->size += 1;
	return (new);
}

t_command		*ft_pushlast(t_list *list, char *data, int type)
{
	t_command	*new;

	if (!list || !data)
		return (NULL);
	new = (t_command *)ft_malloc(sizeof(*new));
	new->data = data;
	new->type = type;
	new->next = NULL;
	new->prev = list->last;
	if (!list->last)
		list->first = new;
	else
		list->last->next = new;
	list->last = new;
	list->size += 1;
	return (new);
}

void			ft_free_list(t_list **list)
{
	t_command	*tmp;
	t_command	*ftmp;

	tmp = (*list)->first;
	while (tmp)
	{
		free(tmp->data);
		ftmp = tmp;
		tmp = tmp->next;
		free(ftmp);
		ftmp = NULL;
	}
	free(*list);
	*list = NULL;
}

void			ft_printlist(t_list *list)
{
	t_command	*tmp;

	tmp = list->first;
	if (!tmp)
		return ;
	while (tmp && tmp->next)
	{
		ft_putstr("\033[41m");
		ft_putstr(tmp->data);
		ft_putstr(" [");
		ft_putnbr(tmp->type);
		ft_putstr("]");
		ft_putstr("\033[0m");
		ft_putstr(" > ");
		tmp = tmp->next;
	}
	ft_putstr("\033[41m");
	ft_putstr(tmp->data);
	ft_putstr(" [");
	ft_putnbr(tmp->type);
	ft_putstr("]");
	ft_putstr("\033[0m\n");
}
