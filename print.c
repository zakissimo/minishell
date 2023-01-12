/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:24:06 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/12 15:21:09 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_label(t_label label)
{
	printf("Operator: ");
	if (label == INFILE)
		printf("INFILE\n");
	if (label == OUTFILE)
		printf("OUTFILE\n");
	if (label == PIPE)
		printf("PIPE\n");
	if (label == OUTFILE_A)
		printf("OUTFILE (Append)\n");
	if (label == HEREDOC)
		printf("HEREDOC\n");
	if (label == VARIABLE)
		printf("VARIABLE\n");
	if (label == UNKNOWN)
		printf("UNKNOWN\n");
}

void	print_cmds(void)
{
	t_list	*cmd;

	if (g_glob->cmds)
	{
		cmd = *g_glob->cmds;
		while (cmd)
		{
			if (cmd->content)
			{
				printf("cmd_idx: %i\n", (((t_cmd *)cmd->content)->cmd_idx));
				printf("fd_in: %i\n", (((t_cmd *)cmd->content)->fd_in));
				printf("fd_out: %i\n", (((t_cmd *)cmd->content)->fd_out));
				if (!(((t_cmd *)cmd->content)->str))
					printf("cmd is NULL\n");
				else
					printf("cmd: %s\n", (((t_cmd *)cmd->content)->str));
			}
			cmd = cmd->next;
		}
	}
}

void	print_nodes(void *n)
{
	t_token	*node;

	node = (t_token *)n;
	printf("-------------\n");
	printf("TOKEN %d\n", node->idx);
	print_label(node->label);
	printf("Input: \"%s\"\n", node->str);
	printf("At idx %d\n", node->str_idx);
	printf("Arg is %s\n", node->arg);
	printf("-------------\n");
	printf("\n");
}
