/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1single_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 08:20:45 by guilmira          #+#    #+#             */
/*   Updated: 2022/04/12 16:54:05 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_blank(int i, t_arguments *args)
{
	t_list		*list;
	t_command	*command_struct;

	list = NULL;
	command_struct = NULL;
	list = args->commands_lst;
	while (list)
	{
		command_struct = list->content;
		if (command_struct->index == i)
			break ;
		list = list->next;
	}
	if (!ft_strcmp(BLANK, command_struct->command[0]))
		return (1);
	return (0);
}

void
	fork_single_child(t_arguments *args)
{
	int	identifier;
	int	i;
	int	wstatus;

	if (!check_command(args))
		return ;
	identifier = fork();
	if ((identifier) == 0)
	{
		i = single_son(args);
		write_pipe_to(args->wpipe, &i);
		exit(0);
	}
	else if (identifier > 0)
	{
		read_pipe_from(args->wpipe, &i);
		wait(&wstatus);
		mnge_status(args, i);
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
}

/** PURPOSE : Executes fork function for a single command. */
int
	single_process(t_arguments *args)
{
	t_command	*command_struct;
	int			ret;

	set_status(args, 0);
	command_struct = NULL;
	command_struct = get_command_struct(args, command_struct);
	ret = get_builtins_ret(args, command_struct);
	if (ret >= 0 && !command_struct->heredoc_result)
		return (ret);
	if (pipe(args->wpipe) == -1)
	{
		printf("PIPE ERROR: %s\n", strerror(errno));
		set_status(args, 1);
		return (1);
	}
	fork_single_child(args);
	return (1);
}
