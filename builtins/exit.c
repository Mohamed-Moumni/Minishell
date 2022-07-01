/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:41:53 by mmoumni           #+#    #+#             */
/*   Updated: 2022/06/29 22:39:10 by mmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"

void	ft_exit(t_char *args, int condition)
{
	t_char			*temp;
	unsigned char	exit_status;
	int				ret;

	temp = args->next;
	if (temp == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (temp->next)
		{
			printf ("%s: exit: too many arguments", MINISHELL);
			// update the golabal struct
			exit (EXIT_FAILURE);
		}
		if (check_number(args->argv))
		{
			ret = ft_atoi(args->argv);
			exit_status = (unsigned char)ret;
			// upadte the golobal struct
			exit (EXIT_SUCCESS);
		}
	}
}