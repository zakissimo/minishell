/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:30:45 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/02 15:04:44 by zhabri           ###   ########.fr       */
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
# include "libft/includes/libft.h"
# include <unistd.h>

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

extern t_glob	*g_glob;

bool		last_cmd_is_exit(void);
char		**ft_split_sep(char const *s, char *sep);
bool		exit_child(char *cmd);
bool		exit_parent(void);
bool		check_exit_error(char **cmd_split);
void		print_exit_num_error(char *cmd);
bool		is_valid_exit_arg(char *cmd);
bool		overflows_llong(char *str);
bool		str_is_numeric(char *str);
long long	ft_atoll(const char *nptr);
void		handle_sigquit(void);
void		handle_sigint(void);
void		reset_g_glob(void);
char		*get_limiter(t_token *token);
char		*name_generator(void);
void		init_g_glob(void);
void		ignore_sig(int sig);
void		final_clean_up(void);
void		free_null(void *var);
void		init_input(char *str);
char		*get_first(void);
bool		ft_open_out(t_cmd *node, t_token *token);
bool		ft_open_in(t_cmd *node, t_token *token);
void		split_cmds(void);
void		scan_heredocs(void);
void		unlink_heredocs(void);
void		add_to_tab(char **tab, char *str);
void		free_tab(void *t);
void		get_cmd(void);
void		free_op_list(void);
void		get_args(void);
void		get_after_op(void);
int			ft_isprint_nospace(int c);
int			ft_isprint_nospace_nodollar(int c);
void		print_cmds(void);
void		clear_cmds(void);
void		print_nodes(void *n);
void		find_var(t_token *token, char *input);
void		free_token_str(void *n);
void		print_label(t_label label);
char		*remove_quotes(char *str);
int			find_quote(const char *s, char c);
char		*ft_strjoinf(char *s1, char const *s2);
char		*ft_strtrimf(char *s1, char const *set);
void		get_ops(const char *input, t_list **head);
int			pipe_error(void);
int			op_error(void);
void		clear_cmd(void *curr);
t_cmd		*init_cmd_token(int in, int out, char *str, bool reset);
void		lst_dellast(t_list **lst, void (*del)(void *));
char		*op_error_trimmed(t_list *curr);
void		expand(t_token *var);
t_list		**str_tab_to_list(char **tab);
int			quote_error(const char *input);
int			get_longest_str(char *s1, char *s2);
void		insert_node(t_list **head, t_list *node, int idx);
int			skip_if_quotes(const char *s, int i);
char		**ft_split_quotes(char const *s, char *sep);
void		add_cmd(t_token *token, t_list **cmds, bool *pb);
void		pipex(void);
void		child(t_cmd *cmd, int *pipes, int *children_pid);
void		close_pipes(int *pipes);
char		**envp_list_to_tab(void);
void		clean_exit(int *children_pid);
void		print_cmd_not_found(char *str);
void		eof_limiter_not_found(char *here_doc_entry, char *limiter);
void		init_sig_callbacks(int process);
void		exit_on_permission(char **cmd_split, \
			int *pipes, int *children_pid);
void		exit_on_bad_cmd(char **cmd_split, \
			int *pipes, char *cmd, int *children_pid);
void		free_tab_bis(void *t);
void		get_sum(char *cmd, char **ret, int *pipes);
char		*get_path(char *cmd);
void		change_sig_handling(char *cmd, int *pipes);
void		pwd(void);

#endif
