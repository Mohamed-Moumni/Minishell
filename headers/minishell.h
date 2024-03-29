/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:02 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/21 16:11:48 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../headers/struct.h"
# include "../headers/builtins.h"

t_cmds			*next_cmd(t_cmds *cmds);
void			begin_execution(t_cmds *cmds, t_envp **env);
void			run_command(t_cmds *cmds, t_envp **env, int i, int **pipes);
void			trait_redirection(t_cmds *cmd, t_envp *env, int *in, int *out);
void			read_write_herdoc(int *fds, char *str);
void			run_pipe(int **pipes);
void			close_all_pipes(int **pipes);
unsigned int	t_char_size(t_char *tchar_list);
char			**conv_t_char_to_tab(t_char *tchar_list);
unsigned int	how_many_pipes(t_cmds *cmds);
char			*cmd_valid(char *cmd);
char			**std_paths(char *str);
int				check_absolut_path(char *cmd);
int				node_init_cmd(t_cmds **list, t_token token);
int				add_node_cmd(t_cmds **cmds, t_token token);
int				node_char_init(t_char **arg, char *word);
int				add_char_node(t_char **arg, char *word);
void			print_char(t_char *ch);
int				element_count(t_char *list);
t_cmds			*cmd_last_node(t_cmds *cmd);
int				treat_word(t_cmds **cmd, t_lexer *no, t_envp **en, t_token to);
t_char			*char_last_node(t_char *node);
int				adjust_filename(t_cmds **cmd);
int				treat_redir(t_cmds **cmds, t_envp **env, t_lexer *node);
void			print_cmd(t_cmds *cmd);
int				start_execution(t_lexer *list, t_envp **env);
int				**two_dim_arr(int a);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
char			*extract_var(char *start);
int				ft_expand(char	**word, t_envp **env, t_lexer *node);
int				node_init(t_lexer **list, char *word, t_token token);
int				add_node(t_lexer **list, char *word, t_token token);
int				between_quote(char *line, char *operator, char quote);
t_lexer			*get_lexer(char *line);
int				create_node_lex(t_lexer **list, char *line, int *i, int *j);
int				check_last_node(t_lexer *list);
int				check_operator(char *line);
int				split_operator(t_lexer **list, char *line);
int				specify_operator(char *word, t_token *token);
char			*hundle_quote(char	*word, t_envp **env, t_lexer *node);
int				ft_char_counter(char *str, char ch);
int				checkcmp(char *num, int plus, int minus);
int				is_integer(char *num);
int				is_number(char *num);
int				check_number(char *num);
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
int				ft_strlen(char *str);
int				advanced_strlen(char *start, char *end);
int				ft_strcmp(char *s1, char *s2);
char			*ft_substr(char *s, int start, int len);
char			*ft_strchr(char *s, int c);
void			execute_cmd(t_cmds *cmd, t_envp **env);
char			**ft_split(char const *s, char c);
char			*ft_strdup(char *s1);
void			free_cmd_list(t_cmds **cmds);
void			free_lexer(t_lexer **lexer);
void			free_tchar(t_char **tchar);
int				ft_isspace(char c);
void			check_start(t_cmds *cmd, int *infile, int *outfile);
void			sig_handler(int signal);
char			*get_next_line(int fd);
char			*ft_strjoin_gn(char *s1, char *s2);
char			*ft_strchr_gn(char *s, int c);
void			run_one_cmd(t_cmds *cmds, t_envp **env);
void			free_tab(void **tab);
int				open_left_redir(t_cmds *cmds);
void			one_cmd(t_cmds *cmds, t_envp **env);
void			run_command(t_cmds *cmds, t_envp **env, int i, int **pipes);
void			trait_redirection(t_cmds *cmds, t_envp *env, int *in, int *out);
void			execute_cmd(t_cmds *cmd, t_envp **env);
void			run_builtin(t_cmds *cmd, t_envp **env);
void			begin_execution(t_cmds *cmds, t_envp **env);
void			get_exit_status(int status);
void			mutliple_cmds(t_cmds *cmds, t_envp **env, int **pipes);
int				open_left_redir(t_cmds *cmds);
void			is_builtin(t_cmds *cmd, int *res);
t_cmds			*next_cmd(t_cmds *cmds);
char			*check_path(char *path, int *cond);
void			exceve_cmd(t_cmds *cmd, t_envp **env);
int				node_char_init(t_char **arg, char *word);
int				add_char_node(t_char **arg, char *word);
int				element_count(t_char *list);
t_char			*char_last_node(t_char *node);
int				node_init_cmd(t_cmds **list, t_token token);
int				add_node_cmd(t_cmds **cmds, t_token token);
void			add_front_node_cmd(t_cmds **cmd, t_char *tmp, t_token token);
t_cmds			*cmd_last_node(t_cmds *cmd);
int				adjust_heredoc(t_lexer **list);
void			add_front_lexer(t_lexer **head, char *word, t_token token);
void			free_str(char *str1, char *str2, int cond);
char			*ft_strjoin_ad(char *s1, char *s2, int cond);
void			sig_handl(int signal);
void			set_token(t_lexer *node);
#endif
