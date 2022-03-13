/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0command_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:57:04 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/13 14:13:12 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	manage_output(int flag_file, char *file, t_arguments *args)
{
	args->flag_file_out = 1;
	if (args->file_output)
		free(args->file_output);
	if (!file || !file[0])
	{
		args->flag_file_out = -1;
		return ;
	}
	args->file_output = ft_strdup(file);
	if (!args->file_output)
		ft_shutdown(MEM, 1, args);
	if (flag_file == 3)
		create_file_append(file, args);
	else if (flag_file)
		create_file(file, args);
}

/** PURPOSE : Iterate list and create every single file as is needed. 
 *  Flag file indicates if append is needed. */
static void	generate_output(t_list *list_out, int flag_file, t_arguments *args)
{
	while (list_out)
	{
		manage_output(flag_file, list_out->content, args);
		list_out = list_out->next;
	}
}



/* static void	get_input(char *file, t_arguments *args)
{
	if (args->file_input)
		free(args->file_input);
	if (!file)
	{
		args->flag_file_out = -1;
		return ;
	}
	args->file_input = ft_strdup(file);
	if (!args->file_input)
		ft_shutdown(MEM, 1, args);
} */

/** PURPOSE : Iterate list and take inputs. */
/* static void	search_input(t_list *list_in, t_arguments *args)
{
	while (list_in)
	{
		get_input(list_in->content, args);
		list_in = list_in->next;
	}
} */


void	command_file_setup(t_command *command_struct, t_arguments *args)
{
	char	*file;

	file = NULL;
/* 	if (command_struct->list_in)
	{
		search_input(command_struct->list_in, args);
		if (args->file_input)
			input_from_file(args->file_input);
	} */
	if (command_struct->list_out)
	{
    printf("%s\n", command_struct->list_out->content);
		generate_output(command_struct->list_out, command_struct->flag_file, args);
 		if (command_struct->flag_file == 2)
			output_to_file_append(file);
		else if (args->file_output)
			output_to_file(args->file_output);
	}
	

    /* if (args->flag_file_in == -1 || args->flag_file_out == -1)
	{
		if (args->flag_file_in)
			printf("%s: No such file or directory\n", args->file_input);
		if (args->flag_file_in == -1 || args->flag_file_out == -1)
			printf("File or directory not found\n");
		args->flag_execution = 1;
		return (0);
	} */
}
