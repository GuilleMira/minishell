/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:47:02 by asydykna          #+#    #+#             */
/*   Updated: 2022/01/11 18:47:11 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	sig_handler(int signum __attribute__((unused)))
{
	ft_putendl_fd("", 2);
	ft_putstr_fd("msh> ", 2);
}

void
	eof_exit(t_arguments *args)
{
	ft_putendl_fd("", 2);
	ft_putendl_fd("exit", 2);
	free_heap_memory(args); //Check if everything is OK
	exit(EXIT_SUCCESS);
}