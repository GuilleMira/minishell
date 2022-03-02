/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1expansion_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 10:15:06 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/02 10:28:31 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"





char	*build_from_list(t_list *list)
{
	char	*str;
	char	*tmp;
	char	*fragment;

	str = NULL;
	fragment = NULL;
	tmp = NULL;
	str = ft_strdup(list->content);
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

/** PURPOSE : Advance to INMIDATE next piece of variable. */
static int	advance_to_next_variable(char *line, int i)
{
	if (!line)
		return (i);
	while (line[++i])
		if (line[i] == EXPAN || line[i] == ' ' || line[i] == SINGLE)
			break;
	return (i);
}

/** PURPOSE : Reads a string and gets the first 
 * variable found: thisisastring$VARIABLE$SECONDVAR.
 * It will output $VARIABLE and allocate memory for it */
static char	*get_variable_onstring(char *str)
{
	int		i;
	char	*new_str;

	new_str = NULL;
	i = 0;
	while (str[++i])
	{
		if (!str[i + 1])
			new_str = ft_substr(str, 1, i);
		else if (str[i] == ' ' || str[i] == EXPAN || str[i] == SINGLE)
		{
			new_str = ft_substr(str, 1, i - 1);
			break;
		}
	}
	return (new_str);
}


/** PURPOSE : Takes a string, expands $VARIABLES by loading
 * a linked list and then joiniing each node to create a single string result. */
char	*ultra_expansion(char *str, t_arguments *args)
{
	int		i;
	int		t;
	char	*new_str;
	char	*fragment;
	char	*value;
	t_list	*list;


	i = 0;
	t = 0;
	list = NULL;
	new_str = NULL;
	fragment = NULL;
	value = NULL;
	while (str[i])
	{
		if (str[i] == SINGLE)
		{
			i = advance_to_next_quote(str, i);
			fix_previous_line(str, t, i, &list);
			t = i + 1;
		}
		else if (str[i] == EXPAN)
		{
			fragment = get_variable_onstring(&str[i]);
			i = advance_to_next_fragment(str, i);
			t = i + 1;
			value = get_env_var(args->envp, fragment);
			printf("value: %s\n", value);
			ft_lstadd_back(&list, ft_lstnew(value));

			free(fragment);
		}
		else
		{
			while (str[i] && str[i] != EXPAN && str[i] != SINGLE)
				i++;
			fix_previous_line(str, t, i, &list);
			t = i;
		}
		t = i;
	}
	new_str = build_from_list(list);
	ft_fullclear(list);
	return (new_str);
}