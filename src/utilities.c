/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:58:25 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/10 11:35:45 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** SYNOPSIS: function for printing string arrays.
*/
void
	print_str_arr(char *const *arr, int fd)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_putendl_fd(arr[i], fd);
		i++;
	}
}

/*
** SYNOPSIS: calculates number of string in a string array.
*/
size_t
	get_arr_len(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

/*
** SYNOPSIS: allocates memory for elem_num elements of array of type elem_size.
** Returns pointer to array.
*/
void
	**get_arr(size_t elem_num, size_t elem_size)
{
	void	**arr;

	arr = malloc(elem_num * elem_size);
	if (!arr)
		printf("Malloc error");
	return (arr);
}

/*
** SYNOPSIS: copies n entries of src array to dest array.
*/
void
	copy_arr_entries(char **dest, char **src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
}

/*
** SYNOPSIS: counts occurrences of char needle in a string p.
*/
int
	count_chars(char *p, char *needle)
{
	int	n;

	n = 0;
	while (p != NULL)
	{
		p = ft_strnstr(p, needle, ft_strlen(p));
		if (p)
		{
			n++;
			p++;
		}
	}
	return (n);
}
