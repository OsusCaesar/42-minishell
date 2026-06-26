/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrand <jferrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:18:02 by jferrand          #+#    #+#             */
/*   Updated: 2025/10/12 19:03:12 by jferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns 1 if the file is compatible with the wildcard
// Returns 0 otherwise.
int	wildcard_cmp(char *file, char *wildcard)
{
	int	is_wc;

	is_wc = 0;
	while (*wildcard && *file)
	{
		while (*wildcard == WILDCARD_VAL)
		{
			wildcard++;
			is_wc = 1;
		}
		while (is_wc && *file && *wildcard != *file)
			file++;
		is_wc = 0;
		if (*wildcard != *file)
			return (0);
		if (*wildcard)
			wildcard++;
		if (*file)
			file++;
	}
	while (*wildcard == WILDCARD_VAL)
		wildcard++;
	if (!*wildcard && !*file)
		return (1);
	return (0);
}

// Returns a string composed with all the files that correspond to the wildcard
char	*ft_getfilesfromwildcard(char *wildcard)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*file_list;
	char			*file;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	file_list = ft_strdup("");
	entry = readdir(dir);
	entry = readdir(dir);
	entry = readdir(dir);
	while (entry)
	{
		file = entry->d_name;
		if ((file[0] != '.' || (file[0] == '.' && wildcard[0] == '.'))
			&& wildcard_cmp(file, wildcard))
			file_list = ft_strjoin_free(file_list, ft_strjoin(file, " "));
		entry = readdir(dir);
	}
	closedir(dir);
	return (file_list);
}

void	get_wc_bounds(int bounds[2], char *cmd, int index)
{
	int	quote;

	bounds[0] = index;
	bounds[1] = index;
	while (bounds[0] >= 0 && !is_space(cmd[bounds[0]]) && cmd[bounds[0]] != '<'
		&& cmd[bounds[0]] != '>' && cmd[bounds[0]] != '|'
		&& cmd[bounds[0]] != '&')
	{
		quote = is_quote(cmd[bounds[0]]);
		while (quote && is_quote(cmd[--bounds[0]]) != quote)
			continue ;
		bounds[0]--;
	}
	while (cmd[bounds[1]] && !is_space(cmd[bounds[1]]))
	{
		quote = is_quote(cmd[bounds[1]++]);
		if (quote)
		{
			while (cmd[bounds[1]] && is_quote(cmd[bounds[1]]) != quote)
				bounds[1]++;
			if (cmd[bounds[1]])
				bounds[1]++;
		}
	}
}

char	*ft_getwildcard(char *cmd, int bounds[2])
{
	int		i;
	int		quote;
	char	*wildcard;

	wildcard = ft_strdup("");
	if (!wildcard)
		return (NULL);
	quote = 0;
	i = bounds[0] + 1;
	while (i < bounds[1])
	{
		if (!quote && is_quote(cmd[i]))
			quote = is_quote(cmd[i]);
		else if (quote && is_quote(cmd[i]) == quote)
			quote = 0;
		else
			wildcard = str_cat_plus(&wildcard, cmd[i]);
		i++;
	}
	return (wildcard);
}

// returns a string which contains cmd but with the wildcard located at
// index expanded if it exists.
// if the wildcard is not found cmd is returned, else cmd is freed
char	*expand_wildcard(char *cmd, int *index)
{
	int		bounds[2];
	char	*file_list;
	char	*expanded;
	char	*wildcard;

	get_wc_bounds(bounds, cmd, *index);
	wildcard = ft_getwildcard(cmd, bounds);
	file_list = ft_getfilesfromwildcard(wildcard);
	free(wildcard);
	if (!*file_list)
	{
		free(file_list);
		return (cmd);
	}
	expanded = str_replace(file_list, cmd, bounds[0] + 1, bounds[1]);
	free(cmd);
	*index = bounds[0] + ft_strlen(file_list);
	printf("index: %d, str:\"%s\"\n", *index, expanded);
	free(file_list);
	return (expanded);
}
// free(cmd);
