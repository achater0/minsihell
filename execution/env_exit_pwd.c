/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:43:38 by achater           #+#    #+#             */
/*   Updated: 2024/06/30 16:44:07 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env *env_list, char **args)
{
	if (args && args[0])
	{
		printf("env: %s: No such file or directory\n", args[0]);
		return;
	}
	while (env_list)
	{
		if (env_list->value != NULL)
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}

void	ft_exit(char **args, t_list *cmds)
{
	unsigned char	i ;
	int	x;

	x = 0;
	i = 0;
	if (cmds->nbr == 1)
		printf("exit\n");
	while (args && args[x])
		x++;
	if (args && x > 1 && ft_is_number(args[0]) == 1)
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	if (args && x == 1 && ft_is_number(args[0]) == 1)
		i = ft_atoi(args[0]);
	if (args)
	{
		if (ft_is_number(args[0]) == 0)
		{
			printf("minishell: exit: %s: numeric argument required\n", args[0]);
			exit(255);
		}
	}
	exit(i);
}
char	*ft_getcwd(t_env *env_list)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		while (env_list)
		{
			if (ft_strcmp(env_list->key, "PWD") == 0)
				return (env_list->value);
			env_list = env_list->next;
		}
	}
	return (pwd);
}

void	ft_pwd(t_env *env_list)
{
	char	*pwd;

	pwd = ft_getcwd(env_list);
	if (pwd == NULL)
	{
		perror("getcwd");
		return ;
	}
	printf("%s\n", pwd);
}