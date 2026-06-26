/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:07:40 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/12 22:35:20 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_environment	*env;

	(void)argv;
	if (argc > 1)
		return (ft_putendl_fd(NO_ARG, STDERR_FILENO), EXIT_FAILURE);
	printf("\033[2J\033[H");
	setup_signals_main();
	env = ft_cpy_env(envp);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			return (ft_exit(NULL, &env));
		if (input[0])
		{
			add_history(input);
			ft_minishell(&input, env);
		}
		if (input)
			ft_free(&input);
	}
	ft_free_env(&env);
	rl_clear_history();
	return (0);
}

int	ft_minishell(char **input, t_environment *env)
{
	t_token		*head;
	t_pipeline	*pipeline;
	char		*line;

	line = expand_cmd(*input, env, 1);
	if (!line)
		return (1);
	if (!line[0])
		return (free(line), 1);
	head = analyse_str(&line);
	if (!head)
		return (0);
	get_token_full_str(head);
	pipeline = ft_token_to_cmd(head);
	if (!pipeline)
		return (free(line), ft_free_token(&head), 1);
	pipeline_to_tree(&pipeline);
	ft_free_token(&head);
	execute_pipeline(pipeline, env);
	ft_free_pipeline(&pipeline);
	if (*input != line)
		free(line);
	ft_free(input);
	return (1);
}
