/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:17:03 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/14 15:15:24 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_one_of_lexer_symbols(char symbol)
{
	int		i;
	char	*option[TOTAL_SYMBOLS + 1];
	char	*option_name[TOTAL_SYMBOLS + 1];

	if (!symbol)
		return (0);
	init_options(option, option_name);
	i = -1;
	while (option[++i])
		if (symbol == option[i][0])
			return (1);
	return (0);
}


/* static char	*obtain_name(char symbol, char extra)
{
	int		i;
	int		flag;
	char	*option[TOTAL_SYMBOLS + 1];
	char	*option_name[TOTAL_SYMBOLS + 1];

	flag = 0;
	if (extra == '<' || extra == '>')
		flag++;
	init_options(option, option_name);
	i = -1;
	while (option[++i])
	{
		if (flag)
			return (option_name[i]); //A CORREGIR ---- BIG TODO
		if (symbol == option[i][0])
			return (option_name[i]);
	}
	return (0);
} */

void	fix_previous_line(char *line, int t, int i, t_list **list)
{
	size_t	lenght;
	char	*str;

	if (i - 1 < 0)
		return ;
	lenght = i - t;
	str = ft_substr(line, t, lenght);
	if (!str)
		return ;
	ft_lstadd_back(list, ft_lstnew(str));
}

int	is_quote(char symbol)
{
	if (symbol == '\'' || symbol == '"')
		return (1);
	return (0);
}

int	advance_to_next_quote(char *line, int i)
{
	if (!line)
		return (i);
	while (line[i] != '\'' && line[i] != '"')
	{
		if (line[i] == '\'')
		{
			while (line[++i] != '\'')
				;
			i++;
		}
		else if (line[i] == '"')
		{
			while (line[++i] != '"')
				;
			i++;
		}
		else
			return (i);
	}
	return (i);
}

static char	*obtain_symbol(char *line, int i)
{
	char	*str;

	if (line[i + 1] == '<' || line[i + 1] == '>')
	{
		str = ft_substr(line, i, 3);
		if (!str)
			return (NULL);
		str[2] = ' ';
	}
	else
	{
		str = ft_substr(line, i, 2);
		if (!str)
			return (NULL);
		str[1] = ' ';
	}
	return (str);
}

t_list	*build_lexer_list(char *line)
{
	int		i;
	int		t;
	char	*str;
	t_list	*list;

	list = NULL;
	i = 0;
	t = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			i = advance_to_next_quote(line, i);
			i++;
		}
		else if (ft_isspaces(line[i]))
			i++;
		else if (is_one_of_lexer_symbols(line[i]))
		{
			fix_previous_line(line, t, i, &list);
			t = i + 1;
			str = obtain_symbol(line, i);
			if (line[i + 1] == '<' || line[i + 1] == '>')
				i++;
			ft_lstadd_back(&list, ft_lstnew(str));
			i++;
		}
		else
			i++;
	}
	fix_previous_line(line, t, i, &list);
	return (list);
}


he<ls|wc<"jsdhghjsjkgk"""

char *build_new_line(t_list *list)
{
	char	*str;
	char	*tmp;
	char	*fragment;

	str = NULL;
	fragment = NULL;
	tmp = NULL;
	tmp = ft_strdup(" ");
	if (!tmp)
		return (NULL);
	while (list)
	{
		fragment = ft_strjoin(list->content, " ");
		str = ft_strjoin(tmp, fragment);
		if (!str)
			return (NULL);
		free(tmp);
		tmp = str;
		list = list->next;
	}
	return (str);
}