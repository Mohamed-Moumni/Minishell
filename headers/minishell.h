/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:02 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/15 18:14:18 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include "../headers/struct.h"
#include "../headers/builtins.h"

t_cmds			*next_cmd(t_cmds *cmds);
void			begin_execution(t_cmds *cmds, t_envp *env);
void			run_command(t_cmds *cmds, t_envp *env, int i, int **pipes);
void			trait_redirection(t_cmds *cmds, t_envp *env, int *infile, int *outfile);
void			read_write_herdoc(int *fds, char *str);
void			run_pipe(int **pipes);
void			close_all_pipes(int **pipes);
unsigned int	t_char_size(t_char *tchar_list);
char			**conv_t_char_to_tab(t_char *tchar_list);
unsigned int	how_many_pipes(t_cmds *cmds);
char			*cmd_valid(char *cmd);
char			**std_paths(char *str);
int				check_absolut_path(char *cmd);
int				node_init_cmd(t_cmds **list, e_token token);
int				add_node_cmd(t_cmds **cmds, e_token token);
int				node_char_init(t_char **arg, char *word);
int				add_char_node(t_char **arg, char *word);
void			print_char(t_char *ch);
int				element_count(t_char *list);
t_cmds			*cmd_last_node(t_cmds *cmd);
int				treat_word(t_cmds **cmds, t_lexer *node, t_envp *env, e_token token);
t_char			*char_last_node(t_char *node);
int				adjust_filename(t_cmds *cmd);
int				treat_redir(t_cmds **cmds, t_envp *env, t_lexer *node);
void			print_cmd(t_cmds *cmd);
int				start_execution(t_lexer *list, t_envp *env);
int				**two_dim_arr(int a);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
char			*extract_var(char *start);
int				ft_expand(char	**word, t_envp *env, t_lexer *node);
int				node_init(t_lexer **list, char *word, e_token token);
int				add_node(t_lexer **list, char *word, e_token token);
int				between_quote(char *line, char *operator, char quote);
t_lexer			*get_lexer(char *line);
int				create_node_lex(t_lexer **list, char *line, int *i, int *j);
int				check_last_node(t_lexer *list);
int				check_operator(char *line);
int				split_operator(t_lexer **list, char *line);
int				specify_operator(char *word, e_token *token);
char			*hundle_quote(char	*word, t_envp *env, t_lexer *node);
int				ft_char_counter(char *str, char ch);
int				checkcmp(char *num, int plus, int minus);
int				is_integer(char *num);
int				is_number(char *num);
int				check_number(char **num);
char			*ft_strrchr(char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdupi(const char *s1, int l);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_itoa(int n);
t_envp			*ft_list_last(t_envp *env_list);
size_t			ft_strlcat(char *dst, char *src, size_t dstsize);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
size_t			ft_strlcpy(char *dst, char *src, size_t dstsize);
char			*ft_strstr(char *str, char *to_find);
char			*ft_strtrim(char *s1, char *set);
void			free_list(t_lexer *list);
void			print_lexer(t_lexer *list);
void			free_tab(char **tab);
int				ft_strlen(char *str);
int				advanced_strlen(char *start, char *end);
int				ft_strcmp(char *s1, char *s2);
char			*ft_substr(char *s, int start, int len);
char			*ft_strchr(char *s, int c);
void            execute_cmd(t_cmds *cmd, t_envp *env);
char            **ft_split(char const *s, char c);
char            *ft_strdup(char *s1);
#endif


// int		ft_strlen(char *str);
// char	*ft_strchr(char *s, int c);
// int		ft_strcmp(char *s1, char *s2);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// int		advanced_strlen(char *start, char *end);
// char	*ft_substr(char *s, int start, int len);
// char	*ft_strdupi(const char *s1, int l);
// char	*ft_strjoin(char *s1, char *s2);
// char	*ft_strrchr(char *s, int c);
// char	*ft_strtrim(char *s1, char *set);
// size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
// char	*ft_strncpy(char *dest, char *src, unsigned int n);


// char	*hundle_quote(char	*word, t_envp *env, t_lexer *node);
// char	*add_before_quote(char *quote, char *line);
// char	*quote_handle(char **word, char *line, char *start);
// int		between_quote(char *line, char *operator, char quote);
// t_lexer	*get_lexer(char *line);
// void	print_lexer(t_lexer *list);
// int		create_node_lex(t_lexer **list, char *line, int *i, int *j);
// int		add_node(t_lexer **list, char *word, e_token token);
// int		node_init(t_lexer **list, char *word, e_token token);
// int		check_last_node(t_lexer *list);
// int		check_operator(char *line);
// int		split_operator(t_lexer **list, char *line);
// int		specify_operator(char *word, e_token *token);
// void	free_list(t_lexer *list);
// void	print_lexer(t_lexer *list);
// void	free_tab(char **tab);

// void	remove_quote(char **word);
// void	check_option(char *word, e_token *token);
// void	check_term(char **word, e_token *token);
// char	*split_redirection(t_lexer **list, char *word);
// e_token	ft_tokenize(char **word);
// int 	start_execution(t_lexer *list, t_envp *env);


// char	*ft_itoa(int n);
// int		ft_expand(char	**word, t_envp *env, t_lexer *node);


// char            *ft_strdup(char *s1);
// char            *get_next_line(int fd);
// void            write_in_file(int fd);
// char            **conv_t_char_to_tab(t_char *tchar_list);
// unsigned int	t_char_size(t_char *tchar_list);
// char            **list_to_envp(t_envp *env_list);
// unsigned int	t_envp_size(t_envp *env_list);
// unsigned int	how_many_pipes(t_cmds *cmds);
// void            index_cmds(t_cmds **cmds);
// char			**ft_split(char const *s, char c);
// size_t			ft_strlcpy(char *dst, char *src, size_t dstsize);
// char			*ft_strjoin_leak(char *s1, char *s2, int cond);
// int             ft_isdigit(int c);

// int				**pipes_allocat(int n);
// void			run_pipes(int **pipes, int n);
// int				**two_dim_arr(int a);
// t_cmds			*next_cmd(t_cmds *cmds);
// void			begin_execution(t_cmds *cmds, t_envp *env);
// void			run_command(t_cmds *cmds, t_envp *env, int i, int **pipes);
// void			trait_redirection(t_cmds *cmds, t_envp *env, int *infile, int *outfile);
// void			execute_cmd(t_cmds *cmd, t_envp *env);
// void			run_pipe(int **pipes);
// void			close_all_pipes(int **pipes);
// void	ft_export(t_envp *env, t_char *args);
// void	add_export_vars(t_envp **env, t_char *args);
// void	trait_arg(t_envp **env, t_char *arg);
// void	get_key_value(char *str, char **key, char **value, int cond);
// int	valid_arg(char *str);