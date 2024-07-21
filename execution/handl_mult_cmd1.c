/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_mult_cmd1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:04:48 by achater           #+#    #+#             */
/*   Updated: 2024/07/21 11:04:54 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_fct2(t_list **list, int fd[2], int pid[(*list)->nbr])
{
	int	status;
	int	i;

	close(fd[0]);
	i = -1;
	while (++i < (*list)->nbr)
		waitpid(pid[i], &status, 0);
	exit_status(WEXITSTATUS(status));
	free(pid);
}
