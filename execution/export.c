/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:50:01 by achater           #+#    #+#             */
/*   Updated: 2024/07/04 11:04:29 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_copy_list(t_env *env_list)
{
	t_env *new;
	t_env *tmp;

	new = NULL;
	tmp = env_list;
	while (tmp)
	{
		ft_lstadd_back(&new, ft_lstnew(tmp->key, tmp->value));
		tmp = tmp->next;
	}
	return (new);
}
void	swap_nodes(t_env *node1, t_env *node2)
{
	char *swap_key ;
	char *swap_value;

	swap_value = node1->value;
	swap_key = node1->key;
	node1->key = node2->key;
	node1->value = node2->value;
	node2->key = swap_key;
	node2->value = swap_value;
}


void	sort_and_print_env(t_env *lst, int (*cmp)(char*,char*))
{
	t_env	*tmp;

	tmp = lst;
	if (lst == NULL)
		return;
	while(lst->next != NULL)
	{
		if (((*cmp)(lst->key, lst->next->key)) > 0)
		{
			swap_nodes(lst, lst->next);
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	while (lst)
	{
		if ((*cmp)(lst->key, "_") != 0 && lst->value != NULL)
			printf("declare -x %s=\"%s\"\n", lst->key, lst->value);
		else if ((*cmp)(lst->key, "_") != 0 && lst->value == NULL)
			printf("declare -x %s\n", lst->key);
		lst = lst->next;
	}
}
int	key_exist(t_env *env, char *key)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}


void	split_by_equal(char *str, char **key, char **value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[i] == '=')
	{
		(*key) = NULL;
		(*value) = NULL;
		return;
	}
	while (str[i] && str[i] != '=')
		i++;
	(*key) = malloc(i + 1);
	i = -1;
	while (str[++i] && str[i] != '=')
		(*key)[i] = str[i];
	(*key)[i] = '\0';
	if (str[i] == '\0')
	{
		(*value) = NULL;
		return;
	}
	(*value) = ft_strdup(str + i + 1);
}

void	free_list(t_env **env)
{
	t_env *tmp;
	t_env *tmp1;

	tmp = *env;
	while (tmp)
	{
		tmp1 = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = tmp1;
	}
	*env = NULL;
}

void	ft_export(char **args, t_env **env)
{
	t_env *tmp;
	t_env *tmp1;
	int i = 0;
	char *key;
	char *value;

	tmp = ft_copy_list(*env);
	tmp1 = *env;
	if (args == NULL)
	{
		sort_and_print_env(tmp, ft_strcmp);
		// free_list(&tmp);
		return ;
	}
	else
	{
		while (args[i])
		{
			if(args[i][0] == '\0')
			{
				printf("minishell: export: `': not a valid identifier\n");
				i++;
				continue;
			}
			split_by_equal(args[i], &key, &value);
			if (key == NULL)
			{
				printf("minishell: export: `=': not a valid identifier\n");
				i++;
				continue;
			}
			if (check_args(key, "export") == 1 || (key[ft_strlen(key) - 1] == '+' && value == NULL))
			{
				printf("minishell: export: `%s': not a valid identifier\n", args[i]);
				i++;
				free(key);
				continue;
			}
			else
			{
				if (key[ft_strlen(key) - 1] != '+')
				{
					if (key_exist(*env, key) == 0)
						ft_lstadd_back(env, ft_lstnew(key, value));
					else
					{
						if (value == NULL)
						{
							i++;
							free(key);
							continue;
						}
						else
						{
							while(tmp1)
							{
								if (ft_strcmp(tmp1->key, key) == 0)
								{
									tmp1->value = value;
									break;
								}
								tmp1 = tmp1->next;
							}
						}
					}
				}
				else
				{
					key[ft_strlen(key) - 1] = '\0';
					if (key_exist(*env, key) == 0)
						ft_lstadd_back(env, ft_lstnew(key, value));
					else
						while(tmp1)
						{
							if (ft_strcmp(tmp1->key, key) == 0)
							{
								tmp1->value = ft_strjoin(get_env_value(key, tmp1), value);
								break;
							}
							tmp1 = tmp1->next;
						}
				}
			}
			i++;
		}
	}
}
