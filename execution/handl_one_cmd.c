/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_one_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:15:20 by achater           #+#    #+#             */
/*   Updated: 2024/07/03 11:16:48 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

 int	check_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd,"env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "PWD") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return(1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	child_help(t_list *cmds, t_env **env_list, char **new_env)
{
		dup2(cmds->file_in, STDIN_FILENO);
		dup2(cmds->file_out, STDOUT_FILENO);
		if (cmds->file_in != 0)
			close(cmds->file_in);
		if (cmds->file_out != 1)
			close(cmds->file_out);
		if (ft_strcmp(cmds->cmd, "echo") == 0)
			ft_echo(cmds->args, 0, 0, 0);
		else if (ft_strcmp(cmds->cmd, "env") == 0 && cmds)
			ft_env(*env_list, cmds->args);
		else if (ft_strcmp(cmds->cmd, "export") == 0 && cmds->args == NULL)
			ft_export(cmds->args, env_list);
		else if (ft_strcmp(cmds->cmd, "pwd") == 0 || ft_strcmp(cmds->cmd, "PWD") == 0)
			ft_pwd(*env_list);
		if(check_builtins(cmds->cmd) == 1)
			exit(0);
		else
			handle_cmd(cmds, new_env);
}

void	handle_one_cmd(t_list *cmds, t_env **env_list)
{
	int	pid;
	char	**new_env;

	new_env = struct_to_char(*env_list);
	handle_redir(cmds, 0);
	if (cmds->file_in < 0)
		return ;
	if (cmds->file_out < 0)
		return ;
	if (ft_strcmp(cmds->cmd, "cd") == 0)
		ft_cd(cmds->args, *env_list);
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		ft_unset(env_list,cmds->args);
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		ft_exit(cmds->args, cmds);
	else if (ft_strcmp(cmds->cmd, "export") == 0 && cmds->args != NULL)
		ft_export(cmds->args, env_list);
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
		child_help(cmds, env_list, new_env);
	else
		wait(NULL);
	free(new_env);
}