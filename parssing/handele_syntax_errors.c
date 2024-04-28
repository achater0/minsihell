/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handele_syntax_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:55:56 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/28 15:15:14 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handele_error()
{
    printf("=> " ANSI_BACKGROUND_RED     "syntax error"     ANSI_RESET_ALL "\n");
}
// int  check_tab(t_list **list, char *line)
// {
//     (void)line;
//     int i = 0;
//     while (list[i])
//     {
//         if ((list[i]->redir[0] == '<' || list[i]->redir[0] == '<' || list[i]->redir[0] == '|') && list[i]->redir[1] == '\0')
//             return 1;
//         i++;
//     }
//     return 0;
// }

int count_quote(char *line, int len)
{
    int count = 0;
    while (*line && len > 0)
    {
        if (*line == '\"' || *line == '\'')
            count++;
        line++;
        len--;
    }
    return (count % 2);
}