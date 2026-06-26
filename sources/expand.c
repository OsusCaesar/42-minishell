/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:24:29 by jferrand          #+#    #+#             */
/*   Updated: 2025/10/13 15:41:00 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *var_name, t_environment *env)
{
	int	var_len;

	var_len = ft_strlen(var_name);
	if (var_len == 0)
		return (ft_strdup(""));
	if (var_len == 1 && var_name[0] == '?')
		return (ft_itoa(g_exit_status));
	while (env)
	{
		if (!ft_strncmp(var_name, env->name, var_len) && !env->name[var_len])
			return (ft_strdup(env->content));
		env = env->next;
	}
	return (ft_strdup(""));
}

// replaces the part of the string original from start to end
// with the string new
char	*str_replace(char *new, char *original, int start, int end)
{
	int		new_len;
	int		original_len;
	int		old_len;
	int		i;
	char	*replaced;

	old_len = end - start;
	original_len = ft_strlen(original);
	new_len = ft_strlen(new);
	replaced = malloc(sizeof(char) * (original_len + new_len - old_len + 1));
	if (!replaced)
		return (NULL);
	i = 0;
	while (i < (original_len + new_len - old_len + 1))
	{
		if (i < start)
			replaced[i] = original[i];
		else if (i < start + new_len)
			replaced[i] = new[i - start];
		else
			replaced[i] = original[i - (new_len - old_len)];
		i++;
	}
	return (replaced);
}

void	ft_end_exp_env(char *var_name, char *var_content, char *cmd, int *index)
{
	free(var_name);
	free(var_content);
	free(cmd);
	*index -= 1;
}

// returns a string which contains cmd but with the env variable located at
// index expanded.
// if the var is found it's replaced by its content,
// else it's replaced by empty string.
char	*expand_env(char *cmd, int *index, t_environment *env, int db_quote)
{
	int		i;
	char	*var_name;
	char	*var_content;
	char	*expanded;

	i = *index + 1;
	if (cmd[i] == '?')
	{
		var_name = ft_strdup("?");
		i++;
	}
	else
	{
		while (ft_isalnum(cmd[i]) || cmd[i] == '_')
			i++;
		if (i == *index + 1 && (!is_quote(cmd[i]) || (db_quote
					&& is_quote(cmd[i]) == DB_QUOTE_VAL)))
			return (cmd);
		var_name = ft_strndup(cmd + *index + 1, i - *index - 1);
	}
	if (!var_name)
		return (NULL);
	var_content = ft_getenv(var_name, env);
	expanded = str_replace(var_content, cmd, *index, i);
	return (ft_end_exp_env(var_name, var_content, cmd, index), expanded);
}

void	ft_end_exp_cmd(char *cmd, char **exp, t_environment *env, int env_or_wc)
{
	if (*exp && env_or_wc == 1)
		*exp = expand_cmd(*exp, env, 2);
	if (cmd && env_or_wc == 2)
		free(cmd);
}
