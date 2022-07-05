/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:02 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/05 14:53:38 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../headers/struct.h"

int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		advanced_strlen(char *start, char *end);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdupi(const char *s1, int l);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strrchr(char *s, int c);
char	*ft_strtrim(char *s1, char *set);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strncpy(char *dest, char *src, unsigned int n);

char	*hundle_quote(char	*word, t_envp *env, t_lexer *node);
char	*add_before_quote(char *quote, char *line);
char	*quote_handle(char **word, char *line, char *start);
int		between_quote(char *line, char *operator, char quote);
t_lexer	*get_lexer(char *line);
void	print_lexer(t_lexer *list);
int		create_node_lex(t_lexer **list, char *line, int *i, int *j);
int		add_node(t_lexer **list, char *word, e_token token);
int		node_init(t_lexer **list, char *word, e_token token);
int		check_last_node(t_lexer *list);
int		check_operator(char *line);
int		split_operator(t_lexer **list, char *line);
int		specify_operator(char *word, e_token *token);
void	free_list(t_lexer *list);
void	print_lexer(t_lexer *list);
void	free_tab(char **tab);

void	remove_quote(char **word);
void	check_option(char *word, e_token *token);
void	check_term(char **word, e_token *token);
char	*split_redirection(t_lexer **list, char *word);
e_token	ft_tokenize(char **word);
int 	start_execution(t_lexer *list, t_envp *env);


char	*ft_itoa(int n);
int		ft_expand(char	**word, t_envp *env, t_lexer *node);

// Get_next_line 

char            *ft_strdup(char *s1);
char            *get_next_line(int fd);
void            write_in_file(int fd);
char            **conv_t_char_to_tab(t_char *tchar_list);
unsigned int	t_char_size(t_char *tchar_list);
char            **list_to_envp(t_envp *env_list);
unsigned int	t_envp_size(t_envp *env_list);
unsigned int	how_many_pipes(t_cmds *cmds);
void            index_cmds(t_cmds **cmds);

char	**ft_split(char const *s, char c);

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strjoin_leak(char *s1, char *s2, int cond);

t_exec	*execute_node(t_cmds *cmd, t_cmds *file, int inf, int outf);
t_exec	*last_exec(t_exec *exec);
void	exec_add_back(t_exec **exec, t_exec *new);
void	add_command(t_exec **exec, t_cmds *cmd, t_cmds *file);
int     open_file(char *path, e_token token);
int     file_exist(char *path);
t_cmds  *check_redirection(t_exec **exec, t_cmds *cmd, int **pipe, int i);
int     **pipes_allocat(int n);
void    run_pipes(int **pipes, int n);
t_exec  *cmds_to_exec(t_cmds *cmds);
void	print_exec(t_exec *exec);
#endif