/*
** my_str_to_wordtab.c for CPool_Day08.c in /home/cedric/delivery/CPool_Day08/task04
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Oct 12 12:19:23 2016 Cédric Thomas
** Last update Thu Jan 12 15:32:30 2017 
*/
#include <stdlib.h>
#include "mysh.h"
#include "my.h"
#include "my_printf.h"

char	*dequotificator(char *str)
{
  char	*dequoted;
  char	quote;
  int	i;
  int	nb;

  i = -1;
  quote = 0;
  nb = 0;
  while (str[++i])
    if (quote == 0 && is_in(str[i], QUOTE) || str[i] == quote)
      quote = (!quote ? str[i] : 0) + 0 * (nb++);
  if ((dequoted = malloc(sizeof(char) * (my_strlen(str) + 1 - nb))) == NULL)
    return (NULL);
  dequoted[my_strlen(str) - nb] = 0;
  i = -1;
  nb = 0;
  while (str[++i])
    if (quote == 0 && is_in(str[i], QUOTE) || str[i] == quote)
      quote = (!quote ? str[i] : 0) + 0 * (nb++);
    else
      dequoted[i - nb] = str[i];
  free(str);
  return (dequoted);
}

int	get_nbr_args(char *str)
{
  int           i;
  char          quote;
  int           words;
  int           find;

  i = -1;
  words = 0;
  quote = 0;
  find = 0;
  while (str && str[++i])
    {
      if (quote == 0 && is_in(str[i], QUOTE) || str[i] == quote)
	quote = (!quote ? str[i] : 0);
      if (is_in(str[i], ARG_P) && find && !quote)
	{
	  words += 1;
	  find = 0;
	}
      if (str[i] == quote || !quote && !is_in(str[i], ARG_P))
	find = 1;
    }
  return (words + find);
}

char	**split_that(char *str, char **tab, int size)
{
  int	index;
  int	lindex;
  int	len;
  int	i;

  i = -1;
  index = 0;
  lindex = index;
  skipthat(str, &index, ARG_P);
  while (++i < size)
    {
      len = my_token_len(str, ARG_P, &index);
      tab[i] = my_strndup(str + lindex, len);
      tab[i] = dequotificator(tab[i]);
      lindex = index;
    }
  tab[i] = NULL;
  return (tab);
}

t_cmmd	*get_args(t_cmmd *cmds)
{
  int	i;
  int	currentsize;

  i = -1;
  while (cmds && cmds[++i].cmd)
    {
      currentsize = get_nbr_args(cmds[i].cmd);
      if ((cmds[i].argv = malloc(sizeof(char *) * (currentsize + 1))) == NULL)
      	return (NULL);
      cmds[i].argv = split_that(cmds[i].cmd, cmds[i].argv, currentsize);
      cmds[i].argc = currentsize;
    }
  return (cmds);
}
