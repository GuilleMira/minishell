/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0dollar_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:21:40 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/02 11:46:05 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Evaluates whether there is a $ that is not locate
 * between single quotes ('$USER', this should not expand.) */
int	needs_expansion(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		printf("aqui\n");
		if (!ft_strchr(&str[i], EXPAN))
			return (0);
		if (str[i] == SINGLE)
		{
			
			i = advance_to_next_quote(str, i);
			printf("%i\n", i);
			if (!str[i])
				break;
		}
		else if (str[i] == EXPAN && str[i + 1])
		{
			if (str[i + 1] != SINGLE && str[i + 1] != DOUBLE && str[i + 1] != EXPAN)
				return (1);
			i++;
		}
		else
			i++;
		
	}
	return (0);
}

/** PURPOSE : Takes a table of strings and expands variables.
 * This is finding the $ symbol, tkaen the variable ad substitute
 * said variable for its value. Some examples: 
 * export alfa=l   export beta=s  COMMAND  $alfa$beta
 * 	--> 	table[0] = ls (output result, ls) */
char	**dollar_expansion(char **table, t_arguments *args)
{

	int		i;
	char	*new_str;
	char	*str;

	i = -1;
	new_str = NULL;
	str = NULL;
	while (table[++i])
	{
		str = table[i];
		if (needs_expansion(str))
		{
			new_str = ultra_expansion(str, args);
			free(str);
			table[i] = new_str;
		}
	}
	
	return (table);
}