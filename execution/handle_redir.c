/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:34:20 by achater           #+#    #+#             */
/*   Updated: 2024/07/26 16:10:58 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	help_error()
{
	perror("minishell");
	return (1);
}

int	redir_helper(t_list *list, int i, int x)
{
	if (x == 1 || x == 2)
	{
		if (list->file_out > 2)
			close(list->file_out);
		if (x == 1)
			list->file_out = open(list->redir[i + 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (x == 2)
			list->file_out = open(list->redir[i + 1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (list->file_out < 0)
			return (help_error());
	}
	if (x == 3)
	{
		if (list->file_in > 2)
			close(list->file_in);
		list->file_in = open(list->redir[i + 1], O_RDONLY);
		if (list->file_in < 0)
			return (help_error());
	}
	return (0);
}

void	handle_redir_no_command(t_list *list, int i)
{
	while (list->redir[i])
	{
		if (ft_strcmp(list->redir[i], ">") == 0)
		{
			if (redir_helper(list, i, 1) != 0)
				return ;
			close(list->file_out);
		}
		else if (ft_strcmp(list->redir[i], ">>") == 0)
		{
			if (redir_helper(list, i, 2) != 0)
				return ;
			close(list->file_out);
		}
		else if (ft_strcmp(list->redir[i], "<") == 0)
		{
			if (redir_helper(list, i, 3) != 0)
				return ;
			close(list->file_in);
		}
		i += 2;
	}
}

void	handle_redir(t_list *list, int i)
{
	if (list->redir == NULL)
		return ;
	while (list->redir[i])
	{
		if (ft_strcmp(list->redir[i], ">") == 0)
			if (redir_helper(list, i, 1) != 0)
				return ;
		if (ft_strcmp(list->redir[i], ">>") == 0)
			if (redir_helper(list, i, 2) != 0)
				return ;
		if (ft_strcmp(list->redir[i], "<") == 0)
			if (redir_helper(list, i, 3) != 0)
				return ;
		if (ft_strcmp(list->redir[i], "<<") == 0)
		{
			if (list->file_in > 3)
				close(list->file_in);
			list->file_in = list->here_doc;
		}
		i += 2;
	}
}

// echo "$?" leeaks

// bash-3.2$ export x="'"
// bash-3.2$ echo "$x"kkkk"$x"

//empty line  should reset exit status to 0
