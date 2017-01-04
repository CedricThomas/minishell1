/*
** misc.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Jan  4 12:55:32 2017 Cédric Thomas
** Last update Wed Jan  4 21:21:33 2017 Cédric Thomas
*/
#include <stdlib.h>
#include "my_printf.h"
#include "my.h"
#include "mysh.h"

char	**tabdup(char **tab)
{
  int	i;
  char	**dup;

  i = 0;
  while (tab[i])
    i += 1;
  if ((dup = malloc(sizeof(char *) * (i + 1))) == NULL)
    return (NULL);
  i = 0;
  while (tab[i])
    {
      if ((dup[i] = my_strdup(tab[i])) == NULL)
	return (NULL);
      i += 1;
    }
  dup[i] = NULL;
  return (dup);
}

void	print_prompt(char **ae)
{
  int	i;
  int	count;
  char	*pwd;

  pwd = getkey(ae, "PWD", 0);
  i = my_strlen(pwd);
  count = 0;
  while (i > 0 && count < 2)
    {
      if (pwd[i] == '/')
	count += 1;
      i -= 1;
    }
  my_printf("%s>", pwd + i + 2);
}
