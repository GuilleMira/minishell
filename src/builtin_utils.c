/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:36:14 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/25 06:35:31 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** SYNOPSIS: sets status of executed command.
*/
void
	set_status(t_arguments *arg, int status)
{
	arg->status = status;
}

/*
** SYNOPSIS: frees pointers passed as arguments and sets them to NULL.
** First arguments should indicate the quantity of passed pointers.
*/
void
	free_pointers(int num, ...)
{
	va_list	ap;
	int		i;
	void	*p;

	i = 0;
	va_start(ap, num);
	while (i < num)
	{
		p = va_arg(ap, void *);
		if (p)
		{
			free(p);
			p = NULL;
		}
		i++;
	}
	va_end(ap);
}

char *
	get_env_val(t_arguments *arg, size_t len, const char *tmp)
{
	int		i;
	char	*env;
	char	**arr;

	i = 0;
	while (arg->envp[i])
	{
		if (!ft_strncmp(arg->envp[i], tmp, len))
		{
			env = arg->envp[i];
			arr = ft_split(env, '=');
			env = ft_strdup(arr[1]);
			ft_free_split(arr);
			return (env);
		}
		i++;
	}
	return (NULL);
}

void
	set_shlvl_num(t_arguments *arg)
{
	static bool	shlvl_set;
	char		*tmp;
	int			num;
	char		*num_tmp;

	if (!shlvl_set)
	{
		tmp = get_env_val(arg, 5, "SHLVL");
		if (tmp)
		{
			num = ft_atoi(tmp);
			free(tmp);
			num_tmp = ft_itoa(num + 1);
			tmp = ft_strjoin("SHLVL=", num_tmp);
			free_pointers(1, num_tmp);
			set_new_var(tmp, arg);
			free_pointers(1, tmp);
		}
		shlvl_set = true;
	}
}
