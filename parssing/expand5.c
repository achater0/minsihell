/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:46:15 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/14 04:04:15 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init(t_int *f, char **old_tab, char **new_str)
{
	f->i = 0;
	f->j = 0;
	f->k = 0;
	f->size = ft_size(old_tab);
	f->size2 = ft_size(new_str);
}

static void	change_tab3(char **new_str, char **new_tab, t_int *f)
{
	if (new_str[f->j][0] == '>' || new_str[f->j][0] == '<'
		|| new_str[f->j][0] == '|')
		new_str[f->j] = protect_new_str(new_str[f->j]);
	if (new_tab)
		new_tab[f->i] = ft_strdup(new_str[f->j]);
	f->i++;
	f->j++;
}

int	c_str(char **tab)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (tab && tab[i])
	{
		if (ft_strcmp(tab[i], "") != 0)
			count++;
		i++;
	}
	return (count);
}

static char	**change_tab2(t_int *f, char **old_tab, char **new_str, char *str)
{
	char	**new_tab;

	new_tab = safe_alloc(f->size + f->size2);
	while (f->i < f->size + f->size2)
	{
		if (ft_strcmp(old_tab[f->k], str) == 0)
		{
			while (f->i < f->size + f->size2 && new_str && new_str[f->j])
				change_tab3(new_str, new_tab, f);
			if (old_tab[f->k] && old_tab[f->k + 1])
				f->k++;
			else
				break ;
		}
		if (old_tab[f->k])
		{
			new_tab[f->i] = ft_strdup(old_tab[f->k]);
			f->i++;
			f->k++;
		}
		else
			break ;
	}
	return (new_tab);
}

char	**change_tab(char **old_tab, char *str)
{
	t_int	f;
	char	**new_str;
	char	**new_tab;

	new_str = ft_split(str, ' ');
	if (!new_str)
		return (old_tab);
	init(&f, old_tab, new_str);
	if (f.size2 <= 1)
	{
		free_tab(new_str);
		return (old_tab);
	}
	new_tab = change_tab2(&f, old_tab, new_str, str);
	if (!new_tab)
	{
		free_tab(new_str);
		return (old_tab);
	}
	new_tab[f.i] = NULL;
	free_tab(old_tab);
	free_tab(new_str);
	return (new_tab);
}
