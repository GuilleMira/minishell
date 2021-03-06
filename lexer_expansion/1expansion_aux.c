/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1expansion_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 10:15:06 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/10 21:00:37 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Builds a single string from all nodes. */
char	*build_from_list(t_list *list)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	str = ft_strdup(list->content);
	if (!str)
		return (NULL);
	list = list->next;
	while (list)
	{
		tmp = str;
		str = ft_strjoin(tmp, list->content);
		if (!str)
			return (NULL);
		free(tmp);
		list = list->next;
	}
	return (str);
}

/** PURPOSE : Normi impossed.  */
int	adv_and_fix(char *str, int t, int i, t_list **list)
{
	i = advance_to_next_quote(str, i);
	fix_previous_line(str, t, i, list);
	return (i);
}

/** PURPOSE : Normi impossed.  */
int	norm_and_fix(char *str, int t, int i, t_list **list)
{
	while (str[i] && str[i] != EXPAN && str[i] != SINGLE)
		i++;
	fix_previous_line(str, t, i, list);
	return (i);
}

/** PURPOSE : Takes a string.
 * 1. Expands $VARIABLES by loading a linked list.
 * 2. Joins each node and creates a single string.  */
char	*ultra_expansion(char *str, t_arguments *args)
{
	int		i;
	int		t;
	char	*new_str;
	t_list	*list;

	i = 0;
	t = 0;
	list = NULL;
	new_str = NULL;
	while (str[i])
	{
		if (!str[i])
			break ;
		if (str[i] == SINGLE)
			i = adv_and_fix(str, t, i, &list);
		else if (str[i] == EXPAN)
			i = variable_to_string(str, i, &list, args);
		else
			i = norm_and_fix(str, t, i, &list);
		t = i;
	}
	new_str = build_from_list(list);
	ft_fullclear(list);
	return (new_str);
}
