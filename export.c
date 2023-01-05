/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:56:54 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/05 11:59:22 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

static void	export_no_arg(int fd_out)
{
	int		i;
	char	**envp;
	char	**envp_entry_split;

	envp = envp_list_to_tab();
	sort_ascii(envp);
	i = -1;
	while (envp[++i])
	{
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
		free_tab(envp_entry_split);
	}
	free_tab(envp);
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

static bool	is_valid_identifier(char *identifier)
{
	int		i;
	char	*err;

	i = 1;
	if (!ft_isalpha(identifier[0]) && identifier[0] != '_')
		return (false);
	while (identifier[i])
	{
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
		{
			err = ft_strjoin("minishell: cd: ", identifier);
			err = ft_strjoinf(err, ": not a valid identifier\n");
			ft_putstr_fd(err, 2);
			free(err);
			return (false);
		}	
		i++;
	}
	return (true);
}

static void	handle_export_add(char *var)
{
	char	**var_split;
	t_list	*env_cpy;

	var_split = cut_on_first(var, '=');
	if (is_valid_identifier(var_split[0]))
	{
		env_cpy = get_env_node(var_split[0]);
		if (env_cpy == NULL)
			ft_lstadd_back(g_glob->envp, ft_lstnew(ft_strdup(var)));
		else if (var_split[1][0])
		{
			free(env_cpy->content);
			env_cpy->content = ft_strdup(var);
		}
		free_tab(var_split);
		g_glob->exit_ret = 0;
		return ;
	}
	free_tab(var_split);
	g_glob->exit_ret = 1;
	return ;
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
			free_tab(cmd_split);
			return (true);
		}
		free_tab(cmd_split);
	}
	return (false);
}
