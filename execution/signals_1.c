/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:47:23 by achater           #+#    #+#             */
/*   Updated: 2024/07/24 16:47:43 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_signals(void)
{
	extern int	g_status;

	g_status = 0;
	if (g_status == 0)
	{
		rl_catch_signals = 0;
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
}
