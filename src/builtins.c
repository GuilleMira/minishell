/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:40:28 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/30 10:43:41 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** __attribute__((unused))
** Command for disabling unused variable warnings
*/

/*
** SYNOPSIS: our version of pwd command.
*/
int
	msh_pwd(char **args __attribute__((unused)),
			t_arguments *arg)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		printf("pwd() error: %s\n", strerror(errno));
	ft_putendl_fd(path, 1);
	set_status(arg, 0);
	free(path);
	return (1);
}

/*
** SYNOPSIS: our version of env command.
*/
int
	msh_env(char **args, t_arguments *arg)
{
	char	*str;

	if (get_arr_len(args) > 1)
	{
		set_status(arg, ENOENT);
		str = ft_multistr_concat(2, "env: ", args[1]);
		printf("%s: %s\n", str, strerror(errno));
		free(str);
		set_status(arg, 127);
		return (2);
	}
	print_str_arr(arg->envp, 1);
	set_status(arg, 0);
	return (1);
}

/*
** SYNOPSIS: builtin help command.
*/
int
	msh_help(char **args __attribute__((unused)), t_arguments *arg)
{
	int	i;

	i = 0;
	ft_putendl_fd("\nminishell", 1);
	ft_putendl_fd("Copyright (c) Ardak Sydyknazar "
		"and Guillermo Mira Osuna, 2022.\n", 1);
	ft_putendl_fd("Type program names and arguments, and hit enter.", 1);
	ft_putendl_fd("The following are built in:", 1);
	while (i < msh_num_builtins(arg))
	{
		ft_putstr_fd("\t", 1);
		ft_putendl_fd(arg->builtin_str[i], 1);
		i++;
	}
	ft_putendl_fd("Use the man command for information on other commands.", 1);
	set_status(arg, 0);
	return (1);
}
