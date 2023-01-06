/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:56:54 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/05 14:47:39 by zhabri           ###   ########.fr       */
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
			print_export_line(envp_entry_split, fd_out);
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

static bool	plus_end_str(char *str)
{
	int i;

	i = 0;
	while (str && str[i] && str[i + 1])
		i++;
	if (str && str[i] == '+')
		return (true);
	return (false);
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
		{
			if (!plus_char)
				ft_lstadd_back(g_glob->envp, ft_lstnew(ft_strdup(var)));
			else
				ft_lstadd_back(g_glob->envp, \
					ft_lstnew(ft_strdup(ft_strjoin(var_split[0], var_split[1]))));
		}
			
		else if (var_split[1][0])
		{
			if (!plus_char)
			{
				free(env_cpy->content);
				env_cpy->content = ft_strdup(var);
			}
			else
			{
				if (ft_strchr(env_cpy->content, '='))
					env_cpy->content = ft_strjoinf(env_cpy->content, var_split[1] + 1);
				else
					env_cpy->content = ft_strjoinf(env_cpy->content, var_split[1]);
			}
				
		}
		free_tab(var_split);
		g_glob->exit_ret = 0;
		return ;
	}
	free_tab(var_split);
	g_glob->exit_ret = 1;
}

bool	export_parent(void)
{
	int		i;
	char	**cmd_split;

	if (ft_lstsize(*g_glob->cmds) == 1)
	{
		cmd_split = ft_split_sep(((t_cmd *)(*g_glob->cmds)->content)->str, \
			" \t");
		if (cmd_split[0] && !ft_strncmp(cmd_split[0], "export", 7))
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
