/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:29:29 by achater           #+#    #+#             */
/*   Updated: 2024/07/29 17:29:59 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char *cmd, char **envp)
{
	static int	i = 0;
	static int	x = -1;
	char		*path;
	char		**str;

	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	(1 == 1) && (str = ft_split(envp[i] + 5, ':'), i = -1);
	while (str[++i])
	{
		path = ft_strjoin3(str[i], "/", cmd);
		if (access(path, X_OK) >= 0)
		{
			x = i;
			break ;
		}
		free(path);
	}
	i = -1;
	ft_free(str);
	if (x < 0)
		return (NULL);
	return (path);
}

int	ft_strchr(char *str, char caractere)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == caractere)
			return (1);
		i++;
	}
	return (0);
}

void	execute(char **cmds, char **envp, char *cmd)
{
	struct stat	sb;
	char		*path;
	int			i;

	i = 0;
	path = find_path(cmd, envp);
	if (execve(path, cmds, envp) < 0)
	{
		if (access(cmd, X_OK) >= 0)
			execve(cmd, cmds, envp);
		else if (access(cmd, F_OK) >= 0)
			error_handling(cmd, ": Permission denied", 20, 126);
		if (cmd[0] == '.' && cmd[1] == '\0')
		{
			write(2, "minishell: .: filename argument required\n", 41);
			write(2, ".: usage: . filename [arguments]\n", 33);
			exit(2);
		}
		stat(cmd, &sb);
		if (S_ISDIR(sb.st_mode))
			error_handling(cmd, ": is a directory", 16, 126);
		if (ft_strchr(cmd, '/') != 0)
			error_handling(cmd, ": No such file or directory", 29, 127);
		error_handling(cmd, ": command not found", 20, 127);
	}
}

char	**cmds_whit_args(char *cmd, char **args)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = malloc(sizeof(char *) * (count_args0(args) + 2));
	if (cmds == NULL)
		return (NULL);
	cmds[0] = cmd;
	while (args[i])
	{
		cmds[i + 1] = args[i];
		i++;
	}
	cmds[i + 1] = NULL;
	return (cmds);
}

void	handle_cmd(t_list *cmds, char **env)
{
	char	**args;

	if (cmds->args == NULL)
	{
		args = malloc(sizeof(char *) * 2);
		args[0] = cmds->cmd;
		args[1] = NULL;
	}
	else
		args = cmds_whit_args(cmds->cmd, cmds->args);
	execute(args, env, cmds->cmd);
}
