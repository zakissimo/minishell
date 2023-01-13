/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:30:45 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/13 11:52:07 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <dirent.h>
# include "libft/includes/libft.h"

# define PARENT 0
# define CHILD 1

typedef enum e_label
{
	HEREDOC,
	OUTFILE_A,
	PIPE,
	OUTFILE,
	INFILE,
	VARIABLE,
	UNKNOWN
}			t_label;

typedef struct s_token
{
	t_label			label;
	const char		*str;
	int				str_idx;
	int				idx;
	char			*arg;
	char			*file;
	char			*not_expanded;
}				t_token;

typedef struct s_cmd
{
	int			cmd_idx;
	int			fd_in;
	int			fd_out;
	char		*str;
}				t_cmd;

typedef struct s_glob
{
	t_list			**envp;
	char			*input;
	t_list			**head;
	t_list			**cmds;
	unsigned char	exit_ret;
	bool			in_child;
	bool			sig_int;
	bool			sig_quit;
	bool			here_doc;
	char			*minishell_sum;
}				t_glob;

typedef void	t_builtin(char *cmd, int fd_out);

extern t_glob	*g_glob;

void		add_cmd(t_token *token, t_list **cmds, bool *pb);
void		add_to_tab(char **tab, char *str);
int			builtin(char *cmd);
void		call_builtin(int built_in, t_cmd *cmd, int *pipes, \
				int *children_pid);
void		cd(char *cmd, int fd_out);
bool		cd_parent(void);
void		change_sig_handling(char *cmd, int *pipes, int *children_pid);
bool		check_exit_error(char **cmd_split);
void		child(t_cmd *cmd, int *pipes, int *children_pid);
void		clean_and_free(char **cmd_split);
void		clean_exit(int *children_pid);
void		clear_cmd(void *curr);
void		clear_cmds(void);
void		close_pipes(int *pipes);
char		**cut_on_first(char *str, char sep);
void		echo(char *cmd, int fd_out);
void		edit_var(bool plus_char, char *var, char **var_split, \
				t_list *env_cpy);
void		env(char *cmd, int fd_out);
char		**envp_list_to_tab(void);
void		eof_limiter_not_found(char *here_doc_entry, char *limiter);
void		exit_child(char *cmd, int fd_out);
void		exit_on_bad_cmd(char **cmd_split, \
				int *pipes, char *cmd, int *children_pid);
void		exit_on_error(t_cmd *cmd, char **cmd_split, \
				int *pipes, int *children_pid);
void		exit_on_not_existing_file(char *cmd, char **cmd_split, \
				int *pipes, int *children_pid);
void		exit_on_permission(char **cmd_split, \
				int *pipes, int *children_pid);
bool		exit_parent(void);
void		expand(t_token *var);
void		export(char *cmd, int fd_out);
bool		export_parent(void);
void		final_clean_up(void);
int			find_quote(const char *s, char c);
void		find_var(t_token *token, char *input);
void		free_and_null(char **tmp);
void		free_and_set_exit_ret(char **var_split, int ret);
void		free_null(void *var);
void		free_op_list(void);
void		free_tab(void *t);
void		free_tab_bis(void *t);
void		free_token_str(void *n);
long long	ft_atoll(const char *nptr);
int			ft_isprint_nospace(int c);
int			ft_isprint_nospace_nodollar(int c);
bool		ft_open_in(t_cmd *node, t_token *token);
bool		ft_open_out(t_cmd *node, t_token *token);
char		**ft_split_quotes(char const *s, char *sep);
char		**ft_split_quotes_keep_sep(char const *s, char *sep);
char		**ft_split_sep(char const *s, char *sep);
char		*ft_strjoinf(char *s1, char const *s2);
char		*ft_strtrimf(char *s1, char const *set);
void		get_after_op(void);
void		get_args(void);
void		get_cmd(void);
t_list		*get_env_node(char *var);
char		*get_first(void);
char		*get_home_content(void);
char		*get_limiter(t_token *token);
void		get_sum(char **cmd, char **ret, int *pipes, int *children_pid);
void		get_ops(const char *input, t_list **head);
char		*get_path(char *cmd, bool shaone);
void		handle_sigint(void);
void		handle_sigquit(void);
void		ignore_sig(int sig);
void		infile_exception_tmp(char **second_part, char *arg_split);
void		init_children_pid(int **children_pid, int size);
t_cmd		*init_cmd_token(int in, int out, char *str, bool reset);
void		init_ft_chdir(t_list **pwd, t_list **old_pwd, char **ret);
void		init_g_glob(void);
void		init_new_var(bool plus_char, char *var, char **var_split);
void		init_sig_callbacks(int process);
void		insert_node(t_list **head, t_list *node, int idx);
bool		is_dir(char *cmd);
bool		is_valid_exit_arg(char *cmd);
char		*longest_str(char *s1, char *s2);
void		lst_dellast(t_list **lst, void (*del)(void *));
char		*name_generator(void);
int			op_error(void);
char		*op_error_trimmed(t_list *curr);
bool		overflows_llong(char *str);
int			pipe_error(void);
void		pipex(void);
void		pipex_handle_exit_ret(int children_pid, int exit_ret);
bool		plus_end_str(char *str);
void		print_cmds(void);
void		print_cmd_not_found(char *str);
void		print_error_dir_cd(char *dir);
void		print_exit_num_error(char *cmd);
void		print_export_line(char **envp_entry_split, int fd_out);
void		print_label(t_label label);
void		print_nodes(void *n);
void		pwd(char *cmd, int fd_out);
int			quote_error(const char *input);
char		*remove_quotes(char *str);
void		reset_g_glob(void);
void		scan_heredocs(void);
int			skip_if_quotes(const char *s, int i);
void		sort_ascii(char **envp);
void		split_cmds(void);
int			str_cmp_sort(char *s1, char *s2);
bool		str_is_numeric(char *str);
t_list		**str_tab_to_list(char **tab);
char		**tab_dup(char **tab, int tab_len);
void		unlink_heredocs(void);
void		unset(char *cmd, int fd_out);
bool		unset_parent(void);

#endif
