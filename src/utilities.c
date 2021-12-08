/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:58:25 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/07 11:58:26 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** SYNOPSIS: function for printing string arrays.
*/
void
	print_str_arr(char *const *arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

size_t
	get_arr_len(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void
	**get_arr(int elem_num, size_t elem_size)
{
	void	**arr;

	arr = malloc(elem_num * elem_size);
	if (!arr)
		printf("Malloc error");
	return (arr);
}

void
	copy_arr(char **dest, const char **srs, int src_len)
{
	int	i;

	i = 0;
	while (i < src_len)
	{
		dest[i] = srs[i];
		i++;
	}
}
