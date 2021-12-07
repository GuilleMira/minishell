/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:21:32 by asydykna          #+#    #+#             */
/*   Updated: 2021/11/30 14:21:33 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	init_builtins(void)
{
	g_builtin_str[0] = "echo";
	g_builtin_str[1] = "cd";
	g_builtin_str[2] = "pwd";
	g_builtin_str[3] = "export";
	g_builtin_str[4] = "unset";
	g_builtin_str[5] = "env";
	g_builtin_str[6] = "exit";
	g_builtin_str[7] = "help";
}

char
	**split_line(char *line)
{
	int		bufsize;
	int		position;
	char	**tokens;
	char	*token;

	init_builtins();
	bufsize = TOK_BUFSIZE;
	position = 0;
	tokens = malloc(bufsize * sizeof(char *));
	if (!tokens)
	{
		fprintf(stderr, "msh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		if (position >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "msh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL; //What if position == bufsize?
	return (tokens);
}

/*
** SYNOPSIS: Function for reading a line:
*/
char
	*msh_read_line(void)
{
	char	*line;
	size_t	bufsize;

	line = NULL;
	bufsize = 0;
	if (getline(&line, &bufsize, stdin) == -1) //let getline allocate a buffer for us
	{
		if (feof(stdin)) //TODO: wright your own version
			exit(EXIT_SUCCESS); //exit when EOF received
		else
		{
			perror("readline");
			exit((EXIT_FAILURE));
		}
	}
	return (line);
}

/*
** SYNOPSIS: Basic loop of the shell, does next things:
** Read: Read the command from standard input.
** Parse: Separate the command string into a program and arguments.
** Execute: Run the parsed command.
*/
void
	msh_loop(char *envp[])
{
	char	*line;
	char	**args;
	int		status;

	while (true)
	{
		printf("msh> ");
		line = msh_read_line();
		args = split_line(line);
		status = msh_execute(args, envp);
		free(line);
		free(args);
		if (!status)
			break ;
	}
}

/*
** SYNOPSIS: main function.
*/
int
	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)), char *envp[])
{
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data));
	data->envp = envp;
	data->argv = argv;
	//TODO: decide if we should exit if the program called with arguments
	//TODO: three parts:
	// 1. Load config files, if any.
	// 2. Run command loop.
	msh_loop(envp);
	// 3. Perform shutdown/cleanup
	return (EXIT_SUCCESS);
}
