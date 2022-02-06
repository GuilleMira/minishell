/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1mid_parent_son.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:44 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/16 09:34:27 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Executes forked process for all the mid commands
 * 1. Sets truct of command. Identify its path.
 * 2. Sets the proper inputs and outputs, redirecting the
 * exits (like STDOUT_FILENO) to the correct pipe file descriptor. 
 * 3. Executes command by searching in path with execve. */
static int
	mid_son(int index, t_arguments *args)
{
	t_command	*command_struct;
	char		**cmdwargs;
	int			i;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shutdown(LST, 0, args);
	if (dup2(args->fds[index - 2], STDIN_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(args->fds[index - 2]);
	if (dup2(args->fds[index + 1], STDOUT_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(args->fds[index + 1]);
	cmdwargs = get_cmdwargs(args);
	if (!cmdwargs)
		return (0); //error, no command
	i = 0;
	while (i < msh_num_builtins(args))
	{
		if (ft_strcmp(cmdwargs[0], args->prog->builtin_str[i]) == 0)
			return ((args->builtin_func[i])(cmdwargs, args));
		i++;
	}
	return (execve(command_struct->path, command_struct->command, NULL));
	/*if (execve(command_struct->path, command_struct->command, NULL) == -1)
		ft_shutdown(EXE_ERROR, 0, args);*/
}

/** PURPOSE : Mid process for all the commands that are not
 * wither the  first one or the last one.
 * 1. Establish syntax and index.
 * 2. Forks the process annd creates a single son.
 * 2. Excutes mid_son and waits for it to finish. */
int
	mid_process(t_arguments *args)
{
	int	index;
	int	status;
	int	identifier;

	args->command_number++;
	index = args->command_number * 2;
	if (pipe(&args->fds[index]) == -1)
		ft_shutdown(MSG, 0, args);
	identifier = fork();
	if (identifier == 0)
	{
		close(args->fds[index]);
		g_rv = mid_son(index, args);
		if (g_rv < 0)
			ft_shutdown(EXE_ERROR, 0, args);
		else if (g_rv == 0)
			return (0);
		else
			exit(0); //to avoid duplication
	}
	else if (identifier > 0)
	{
		wait(&status);
		close(args->fds[index + 1]);
		return (g_rv);
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
	return (g_rv);
}
