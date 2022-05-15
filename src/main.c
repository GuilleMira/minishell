/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:32 by asydykna          #+#    #+#             */
/*   Updated: 2022/04/12 16:53:31 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Main loop of the shell.
 * 1. Reads the command from standard input and load it.
 * 2. Execute main routine. Forks commands into processes and execute them. */
int
	shell_loop(char *envp[])
{
	t_prog		*prog;
	t_arguments	*arguments;
	int			ret;
	char		*builtin_str[9];

	prog = NULL;
	arguments = NULL;
	prog = initalize_prog(envp, builtin_str);
	while (true)
	{
		g_rv = 1;
		arguments = initialize_arg(prog);
		set_shlvl_num(arguments);
		shell_reader(arguments);
		if (arguments->flag_execution)
			if (!msh_execute(arguments->argv, arguments))
				break ;
		manage_loop_heap(arguments, prog);
	}
	manage_program_heap(arguments, prog);
	ret = arguments->status;
	free_heap_memory(arguments);
	return (ret);
}

/** EXECUTION : ./minishell
 * This program will run a student made version of the bash console.
 * 		msh> [INSERT COMMANDS]											*/
int	main(int argc, char *argv[] __attribute__((unused)), char *envp[])
{
	rl_event_hook = event;
	set_signal(1);
	if (argc != ARG_NUMBER)
		ft_shut(INVALID_ARGC);
	return (shell_loop(envp));
}
//system("leaks minishell");
//while true ; do leaks -q minishell; sleep 3; done
//lsof -c minishell | grep PIPE
//https://datacarpentry.org/shell-genomics/04-redirection/index.html
