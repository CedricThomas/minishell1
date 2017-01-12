/*
** cmds.c for cmds in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Jan 10 11:41:20 2017 
** Last update Thu Jan 12 17:39:13 2017 Cédric Thomas
*/
#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"
#include "my_printf.h"

int	my_token_len(char *str, char *tf, int *index)
{
  int	i;
  int	quote;

  i = -1;
  quote = 0;
  while (str[++i + *index] && (is_in(str[i + *index], tf) && quote
			       || !is_in(str[i + *index], tf)))
    {
      if ((quote == 0 && is_in(str[i + *index], QUOTE)
	   || str[i + *index] == quote))
	quote = (!quote ? str[i + *index] : 0);
    }
  *index += i;
  skipthat(str, index, tf);
  return (i);
}

int	get_nbr_cmd(char *str)
{
  int		i;
  char		quote;
  int		words;
  int		find;

  i = -1;
  words = 0;
  quote = 0;
  find = 0;
  while (str && str[++i])
    {
      if (quote == 0 && is_in(str[i], QUOTE) || str[i] == quote)
	quote = (!quote ? str[i] : 0);
      if (is_in(str[i], CMD_P) && find && !quote)
	{
	  words += 1;
	  find = 0;
	}
      if (str[i] == quote ||
	  !quote && !is_in(str[i], CMD_P) && !is_in(str[i], ARG_P))
	find = 1;
    }
  return (words + find);
}

static int      checkdouble(char *str)
{
  int		i;
  char		quote;

  i = -1;
  quote = 0;
  while (str && str[++i])
    if (quote == 0 && is_in(str[i], QUOTE) || str[i] == quote)
      quote = (!quote ? str[i] : 0);
  if (quote)
    {
      my_puterror("Unmatched ");
      write(2, &quote, 1);
      my_puterror(".\n");
    }
  return (!quote ? 1 : 0);
}

t_cmmd		*get_token(char *str)
{
  t_cmmd	*cmds;
  int		i;
  int		index;
  int		lindex;
  int		nbr;

  index = 0;
  i = -1;
  if (!checkdouble(str))
    return (NULL);
  while (skipthat(str, &index, CMD_P) || skipthat(str, &index, ARG_P));
  lindex = index;
  nbr = get_nbr_cmd(str);
  if ((cmds = malloc(sizeof(t_cmmd) * (nbr + 1))) == NULL)
    return (NULL);
  while (++i < nbr)
    {
      cmds[i].cmd = my_strndup(str + lindex, my_token_len(str, CMD_P, &index));
      while (skipthat(str, &index, CMD_P) || skipthat(str, &index, ARG_P));
      lindex = index;
    }
  cmds[nbr].cmd = NULL;
  cmds = get_args(cmds);
  return (cmds);
}
