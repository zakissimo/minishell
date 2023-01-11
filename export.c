/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:56:54 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/09 14:22:42 by zhabri           ###   ########.fr       */
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
	i = -1;
	while (envp[++i])
	{
		envp_entry_split = cut_on_first(envp[i], '=');
		if (envp_entry_split && ft_strncmp(envp_entry_split[0], "_", 2))
			print_export_line(envp_entry_split, fd_out);
		free_tab(envp_entry_split);
	}
	free_tab(envp);
	g_glob->exit_ret = 0;
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

static bool	is_valid_identifier(char *identifier, char *var)
{
	int		i;
	char	*err;

	i = 1;
	if (!ft_isalpha(identifier[0]) && identifier[0] != '_')
	{
		err = ft_strjoin("minishell: export: ", var);
		err = ft_strjoinf(err, ": not a valid identifier\n");
		ft_putstr_fd(err, 2);
		free(err);
		return (false);
	}
	while (identifier[i])
	{
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
		{
			err = ft_strjoin("minishell: export: ", var);
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
	char	*tmp;
	char	**var_split;
	bool	plus_char;
	t_list	*env_cpy;

	var_split = cut_on_first(var, '=');
	plus_char = plus_end_str(var_split[0]);
	if (plus_char)
	{
		tmp = ft_substr(var_split[0], 0, ft_strlen(var_split[0]) - 1);
		free(var_split[0]);
		var_split[0] = tmp;
	}
	if (is_valid_identifier(var_split[0], var))
	{
		env_cpy = get_env_node(var_split[0]);
		if (env_cpy == NULL)
			init_new_var(plus_char, var, var_split);
		else if (var_split[1][0])
			edit_var(plus_char, var, var_split, env_cpy);
		free_and_set_exit_ret(var_split, 0);
		return ;
	}
	free_and_set_exit_ret(var_split, 1);
}

bool	export_parent(void)
{
	int		i;
	char	**cmd_split;

	if (ft_lstsize(*g_glob->cmds) == 1)
	{
		cmd_split = ft_split_quotes(((t_cmd *)(*g_glob->cmds)->content)->str, \
			" \t");
		if (cmd_split && cmd_split[0] && !ft_strncmp(cmd_split[0], "export", 7))
		{
			if (!cmd_split[1])
				export_no_arg(((t_cmd *)(*g_glob->cmds)->content)->fd_out);
			else
			{
				i = 0;
				while (cmd_split[++i])
					handle_export_add(cmd_split[i]);
			}
			free_tab(cmd_split);
			return (true);
		}
		free_tab(cmd_split);
	}
	return (false);
}
