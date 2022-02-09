/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1single_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 08:20:45 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/09 13:15:16 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Executes fork function for a single command. */
int
	single_process(t_arguments *args)
{
	int			i;
	int			status;
	int			identifier;
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct->command)
		return (0);
	i = -1;
	while (++i < msh_num_builtins(args))
		if (ft_strcmp(command_struct->command[0], args->prog->builtin_str[i]) == 0)
			return ((args->builtin_func[i])(command_struct->command, args));
	g_rv = 1;
	identifier = fork();
	if (identifier == 0)
	{
		g_rv = single_son(args);
		exit(0);
	}
	else if (identifier > 0)
	{
		//d seg fault en este momento cuand purebo /Users/guilmira/Desktop/kev/ms/minishell
		wait(&status);
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
	return (g_rv);
}
