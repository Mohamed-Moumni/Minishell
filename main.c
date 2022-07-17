/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:47:30 by yait-iaz          #+#    #+#             */
/*   Updated: 2022/07/17 21:57:00 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/struct.h"
#include "./headers/minishell.h"
#include "./headers/builtins.h"

void	replace_content(t_lexer *node)
{
	char	*line;
	char	*double_quote;
	char	*single_quote;
	char	*new_content;

	if (!node)
		return ;
	g_minishell.herdoc = 1;
	double_quote = ft_strchr(node->content, '"');
	single_quote = ft_strchr(node->content, '\'');
	if (double_quote[0] || single_quote[0])
		node->token = SINGLE_QUOTE;
	line = readline("> ");
	if (line == NULL)
	{
		g_minishell.exit_status = 0;
		return ;
	}
	node->content = hundle_quote(node->content, NULL, node);
	new_content = ft_strdupi("", 0);
	while (ft_strcmp(line, node->content) && g_minishell.herdoc != -1)
	{
		if (g_minishell.herdoc == -1)
			line = ft_strdup("\n");
		else
			line = ft_strjoin(line, "\n");
		new_content = ft_strjoin(new_content, line);
		if (line == NULL)
		{
			g_minishell.exit_status = 0;
			break ;
		}
		line = readline("> ");
		// printf("I go out\n");
	}
	free(node->content);
	node->content = new_content;
}

void	adjust_heredoc(t_lexer *list)
{
	t_lexer	*node;

	node = list;
	while (node)
	{
		if (!ft_strcmp(node->content, "<<"))
			replace_content(node->next);
		node = node->next;
	}
}

void	free_tchar(t_char **tchar)
{
	t_char	*temp;
	t_char	*next;

	temp = *tchar;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = next;	
	}
}

void	free_cmd_list(t_cmds **cmds)
{
	t_cmds	*temp;

	temp = *cmds;
	while (temp)
	{
		free_tchar(&temp->argv);
		temp = temp->next;
	}
}

void	free_lexer(t_lexer **lexer)
{
	t_lexer *temp;
	t_lexer	*next;
	
	temp = *lexer;
	while (temp)
	{
		next = temp->next;
		free(temp->content);
		temp = next;
	}	
}

void	set_gminishell(void)
{
	g_minishell.exit_status = 0;
	g_minishell.unset_path = 0;
	g_minishell.sh_level = 2;
	g_minishell.herdoc = 0;
}

int	readline_valid(char *read_line)
{
	int	i;

	i = 0;
	while (read_line[i] && ft_isspace(read_line[i]))
		i++;
	if (!read_line[i])
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_lexer		*list;
	t_envp		*envp;
	char		*read_line;

 rl_getc_function = getc;
   rl_catch_signals = 0;
   rl_catch_sigwinch = 0;
	(void)av;
	(void)ac;
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	set_gminishell();
	envp = envp_to_list(env);
	while (1)
	{
		read_line = readline("minishell$ ");
		if (read_line == NULL)
		{
			g_minishell.exit_status = 0;
			exit (EXIT_SUCCESS);
		}
		add_history(read_line);
		if (!readline_valid(read_line))
		{
			list = get_lexer(read_line);
			if (list)
			{
				adjust_heredoc(list);
				start_execution(list, &envp);
			}
			// free_lexer(&list);
		}
		// free(read_line);
	}
	return (0);
}
