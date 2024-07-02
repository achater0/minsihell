/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:28:38 by achater           #+#    #+#             */
/*   Updated: 2024/07/02 13:23:57 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**struct_to_char(t_env *env_list)
{
	int	i;
	char	**new_env;
	t_env	*temp;

	i = 0;
	temp = env_list;
	new_env = malloc(sizeof(char *) * (ft_lstsize(env_list) + 1));
	if (new_env == NULL)
		return (NULL);
	while (temp)
	{
		if (temp->value == NULL)
			new_env[i] = ft_strjoin3(temp->key, "", "");
		else
			new_env[i] = ft_strjoin3(temp->key, "=", temp->value);
		temp = temp->next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

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

void	ft_builtins(t_list *cmds, t_env **env_list,char **env)
{
	char **new_env;

	(void)env;
	new_env = struct_to_char(*env_list);
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		ft_echo(cmds->args, 0, 0, 0);
	else if (ft_strcmp(cmds->cmd, "cd") == 0)
		ft_cd(cmds->args, *env_list);
	else if (ft_strcmp(cmds->cmd, "env") == 0 && cmds)
		ft_env(*env_list, cmds->args);
	else if (ft_strcmp(cmds->cmd, "export") == 0)
		ft_export(cmds->args, env_list);
	else if (ft_strcmp(cmds->cmd, "pwd") == 0 || ft_strcmp(cmds->cmd, "PWD") == 0)
		ft_pwd(*env_list);
	else if (ft_strcmp(cmds->cmd, "unset") == 0)
		ft_unset(env_list,cmds->args);
	else if (ft_strcmp(cmds->cmd, "exit") == 0)
		ft_exit(cmds->args, cmds);
	else
		handle_cmd(cmds, new_env);
	free(new_env);
}
void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void set_env(char **env, t_env **env_list, int i)
{
	char	**splited_env;
	char	*pdw;

	pdw = getcwd(NULL, 0);
	splited_env = NULL;
	if (env[0] == NULL)
	{
		ft_lstadd_back(env_list, ft_lstnew("PWD", pdw));
		ft_lstadd_back(env_list, ft_lstnew("OLDPWD", NULL));
		ft_lstadd_back(env_list, ft_lstnew("SHLVL", "1"));
		ft_lstadd_back(env_list, ft_lstnew("_", "/usr/bin/env"));
		return;
	}
	while(env[i])
	{
		splited_env = ft_split(env[i], '=');
		if (ft_strcmp(splited_env[0],"SHLVL") == 0)
			splited_env[1] = shlvl_increment(splited_env[1]);
		if (ft_strcmp(splited_env[0],"OLDPWD") == 0)
			ft_lstadd_back(env_list, ft_lstnew("OLDPWD", NULL));
		else
			ft_lstadd_back(env_list, ft_lstnew(splited_env[0], splited_env[1]));
		// ft_free(splited_env);
		i++;
	}
}

void	execution(t_list **list, t_env **env_list, char **env)
{
    int	i;
    int	fd[2];
    pid_t *pid = malloc(sizeof(pid_t) * (*list)->nbr);
    int prev_pipe = -1;

    i = 0;
    (*list)->file_in = 0;
    (*list)->file_out = 1;
    change_env_last_cmd(*list, env_list);
    set_here_doc(list, -1, 0);
    if ((*list)->nbr == 1)
    {
	if((*list)->cmd == NULL && (*list)->redir[0] == NULL)
		return ;
        if ((*list)->redir[0] != NULL && (*list)->cmd == NULL)
		handle_redir_no_command(*list, 0);
	else
            handle_one_cmd(*list, env_list);
    }
    else
    {
        while (i < (*list)->nbr)
        {

        	if (pipe(fd) == -1)
        		error();
        	pid[i] = fork();
        	if (pid[i] == -1)
        		error();
        	if (pid[i] == 0)
            	{
			handle_redir(list[i], 0);
			if (list[i]->file_in < 0)
				exit(EXIT_FAILURE);
			if (list[i]->file_out < 0)
				exit(EXIT_FAILURE);
                	if (i == 0)
               			dup2(list[i]->file_in, STDIN_FILENO);
                	else
                	{
		    		if (list[i]->file_in == 0)
					dup2(prev_pipe, STDIN_FILENO);
		    		else
		    			dup2(list[i]->file_in, STDIN_FILENO);
			 	close(prev_pipe);
                	}

                	if (i != (*list)->nbr - 1)
                	{
				if (list[i]->file_out == 1)
				{
					close(fd[0]);
		    			dup2(fd[1], STDOUT_FILENO);
				}
				else
					dup2(list[i]->file_out, STDOUT_FILENO);
				 close(fd[1]);
                	}
			else
			{
				dup2(list[i]->file_out, STDOUT_FILENO);
				close(fd[1]);
			}
                	if (list[i]->redir[0] != NULL && list[i]->cmd == NULL)
                	{
                	    handle_redir_no_command(*list, 0);
                	    exit(EXIT_SUCCESS);
                	}
                	else
                	{
                		ft_builtins(list[i], env_list, env);
                		exit(EXIT_SUCCESS);
                	}
            	}
            	else
            	{
                	if (i != 0)
                	    close(prev_pipe);
                	prev_pipe = fd[0];
                	close(fd[1]);
        	}
         	if (i != (*list)->nbr - 1)
        	{
			list[i + 1]->file_in = 0;
			list[i + 1]->file_out = 1;
        	}
        	i++;
        }
	int status;
	i = -1;
	while (++i < (*list)->nbr)
		waitpid(pid[i], &status, 0);
	printf("%d\n", WEXITSTATUS(status));
    }
}
