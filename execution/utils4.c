/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:23:28 by achater           #+#    #+#             */
/*   Updated: 2024/07/23 15:57:20 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = -1;
	j = 0;
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = -1;
	j = 0;
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	free(s2);
	return (s3);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

int	count_args0(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
