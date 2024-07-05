/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:49:08 by achater           #+#    #+#             */
/*   Updated: 2024/07/05 13:24:13 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_here_doc(t_list **list, int i, int j)
{
	int	fd[2];
	char	*line;

	while (++i < (*list)->nbr)
	{
		j = 0;
		while (list[i]->redir[j])
		{
			close(list[i]->here_doc);
			// if (i != 0)
			// 	close(list[i - 1]->here_doc);
			if (ft_strcmp(list[i]->redir[j], "<<") == 0)
			{
				if (pipe(fd) == -1)
					error();
				while (1)
				{
					line = readline("> ");
					if (ft_strcmp(line, list[i]->redir[j + 1]) == 0)
					{
						free(line);
						break ;
					}
					write(fd[1], line, ft_strlen(line));
					write(fd[1], "\n", 1);
					free(line);
				}
				close(fd[1]);
				list[i]->here_doc = fd[0];
			}
			j += 2;
		}
	}
}
