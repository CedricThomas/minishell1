/*
** misc.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Thu Jan  5 21:14:52 2017 
** Last update Sun Jan  8 17:50:08 2017 
*/
#include <stdlib.h>
#include "my.h"
#include "mysh.h"

int	is_full_of(char *str, char c)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] != c)
	return (0);
      i += 1;
    }
  return (1);
}

char	*my_strndup(char *str, int n)
{
  int	i;
  char	*dup;

  i = 0;
  if (str == NULL)
    return (NULL);
  if (n > my_strlen(str))
    n = my_strlen(str);
  if ((dup = malloc(sizeof(char) * (n + 1))) == NULL)
    return (NULL);
  dup[n] = 0;
  while (i < n)
    {
      dup[i] = str[i];
      i += 1;
    }
  return (dup);
}

int	skipthat(char *str, int *i, char c)
{
  int	bool;

  bool = 0;
  if (str == NULL)
    return (bool);
  while (str[*i] && str[*i] == c)
    {
      *i += 1;
      bool = 1;
    }
  return (bool);
}

char	*my_getstr(int value)
{
  int	i;
  long	lvalue;
  int	sign;
  char	*nb;

  i = 0;
  lvalue = (value < 0 ? -value : value);
  sign = (value < 0 ? 1 : 0);
  while (value / (++i * 10) != 0);
  if ((nb = malloc(sizeof(char) * (i + sign + 1))) == NULL)
    return (NULL);
  i += sign;
  nb[i] = 0;
  if (sign)
    nb[0] = '-';
  while (--i >= sign)
    {
      nb[i] = (lvalue - (lvalue / 10) * 10) + '0';
      lvalue = lvalue / 10;
    }
  return (nb);
}
