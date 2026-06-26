/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:24:29 by jferrand          #+#    #+#             */
/*   Updated: 2025/10/13 15:42:13 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Expands the environment variables and recalls itself to expand the wildcards.
// Must be called with env_or_wc = 1 so it can expand the env vars and then
// the wildcards.
char	*expand_cmd(char *cmd, t_environment *env, int env_or_wc)
{
	int		i;
	int		sg_quote;
	int		db_quote;
	char	*exp;

	i = 0;
	sg_quote = 0;
	db_quote = 0;
	exp = ft_strdup(cmd);
	while (exp && exp[i])
	{
		if (env_or_wc == 1 && !sg_quote && exp[i] == DOLLAR_VAL)
			exp = expand_env(exp, &i, env, db_quote);
		else if (env_or_wc == 2 && !sg_quote && !db_quote
			&& exp[i] == WILDCARD_VAL)
			exp = expand_wildcard(exp, &i);
		else if (exp && !db_quote && exp[i] == QUOTE_VAL)
			sg_quote = (sg_quote + 1) % 2;
		else if (exp && !sg_quote && exp[i] == DB_QUOTE_VAL)
			db_quote = (db_quote + 1) % 2;
		i++;
	}
	ft_end_exp_cmd(cmd, &exp, env, env_or_wc);
	return (exp);
}
