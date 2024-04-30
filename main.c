/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:35:11 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/30 13:07:40 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int arc, char **arv, char **env)
{
    (void)arc;
    (void)arv;
    char *line;
    t_list **list;
    t_env *env_list;

    line = NULL;
    list = NULL;
    // env = NULL;
    set_env(env, &env_list);
    while (42)
    {
        line = readline("=>  "ANSI_COLOR_YELLOW  "minishell => "   ANSI_RESET_ALL "");
        if (line)
        {
            //parssing
            list = parssing(line);
            if (!list)
                continue;
            //execution
            execution(list, env_list);
        }
    }
}
