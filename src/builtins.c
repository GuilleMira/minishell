/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:40:28 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/10 11:15:32 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** __attribute__((unused))
** Command for disabling unused variable warnings
*/

//TODO: there is a segfault if we send nothing to the program (just press enter) or it is just a symbol;
int
	msh_echo(char **args __attribute__((unused)),
			 t_arguments *arg __attribute__((unused)))
{
	int		i;
	bool	have_option;

	i = 1;
	if (ft_memcmp(args[i], "-n", 3))
		have_option = false;
	else
	{
		have_option = true;
		i += 1;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1); //change hardcoded fd
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!have_option)
		ft_putstr_fd("\n", 1);
	return (1);
}

int
	msh_cd(char **args, t_arguments *arg)
{
	char	*path;
	char	*old_path;

	if (get_arr_len(args) > 2)
	{
		ft_putstr_fd("msh: cd: too many arguments\n", 2);
		return (1);
	}
	path = NULL;
	old_path = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	if (!args[1] || !ft_memcmp(args[1], "~", 2) || !ft_memcmp(args[1], "--", 3))
		path = get_env_var(arg->envp, "HOME=");
	else if (!ft_memcmp(args[1], "-", 2))
		path = get_env_var(arg->envp, "OLDPWD=");
	else
		path = args[1];
	if (chdir(path) != 0)
		perror("msh");
	else
		renew_pwds(arg, old_path);
	free(path);
	free(old_path);
	return (1);
}

int
	msh_pwd(char **args __attribute__((unused)),
			t_arguments *arg __attribute__((unused)))
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		perror("pwd() error");
	printf("%s\n", path);
	return (1);
}

int
	msh_help(char **args __attribute__((unused)),
			 t_arguments *arg __attribute__((unused)))
{
	int	i;

	i = 0;
	printf("minishell\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");
	while (i < msh_num_builtins())
	{
		printf("  %s\n", g_builtin_str[i]);
		i++;
	}
	printf("Use the man command for information on other programs.\n");
	return (1);
}
