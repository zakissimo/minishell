/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:56:54 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/04 14:56:56 by brenaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_no_arg(int fd_out)
{
	int		i;
	char	**envp;
	char	**envp_entry_split;

	envp = envp_list_to_tab();
	sort_ascii(envp);
	i = 0;
	envp_entry_split = NULL;
	while (envp[i])
	{
		free_tab(envp_entry_split);
		envp_entry_split = cut_on_first(envp[i], '=');
		if (envp_entry_split && ft_strncmp(envp_entry_split[0], "_", 2))
		{
			ft_putstr_fd("declare -x ", fd_out);
			ft_putstr_fd(envp_entry_split[0], fd_out);
			if (envp_entry_split[1][0])
			{
				ft_putstr_fd("=\"", fd_out);
				ft_putstr_fd(envp_entry_split[1], fd_out);
				ft_putchar_fd('\"', fd_out);
			}
			ft_putchar_fd('\n', fd_out);
		}
		i++;
	}
}

void	export(char *cmd, int fd_out)
{
	char	**cmd_split;

	cmd_split = ft_split_sep(cmd, " \t");
	if (!cmd_split[1])
		export_no_arg(fd_out);
	close(fd_out);
	clean_and_free(cmd_split);
	exit(0);
}

/*TODO : verif si identifier valable (je crois que que lettres possibles
ou un truc comme ça)
*/

static bool	is_valid_identifier(char *identifier)
{
	(void)identifier;
	return (true);
}

static void	handle_export_add(char *var)
{
	char	**var_split;
	char	**env_entry_split;
	t_list	*env_cpy;

	var_split = cut_on_first(var, '=');
	env_cpy = *g_glob->envp;
	env_entry_split = cut_on_first(env_cpy->content, '=');
	if (is_valid_identifier(var_split[0]))
	{
		while (env_cpy && ft_strncmp(env_entry_split[0], var_split[0], \
		ft_strlen(longest_str(env_entry_split[0], var_split[0])) + 1))
		{
			env_cpy = env_cpy->next;
			if (env_cpy)
			{
				free_tab(env_entry_split);
				env_entry_split = cut_on_first(env_cpy->content, '=');
			}
		}
		if (env_cpy == NULL)
			ft_lstadd_back(g_glob->envp, ft_lstnew(var));
		else if (var_split[1][0])
		{
			free(env_cpy->content);
			env_cpy->content = ft_strdup(var);
		}
	}
	free_tab(var_split);
	free_tab(env_entry_split);
}

bool	export_parent(void)
{
	int		i;
	char	**cmd_split;

	if (ft_lstsize(*g_glob->cmds) == 1)
	{
		cmd_split = ft_split_sep(((t_cmd *)(*g_glob->cmds)->content)->str, \
			" \t");
		if (!ft_strncmp(cmd_split[0], "export", 7))
		{
			if (!cmd_split[1])
				export_no_arg(((t_cmd *)(*g_glob->cmds)->content)->fd_out);
			else
			{
				i = 0;
				while (cmd_split[++i])
					handle_export_add(cmd_split[i]);
			}
			g_glob->exit_ret = 0;
			return (true);
		}
		free_tab(cmd_split);
	}
	return (false);
}
