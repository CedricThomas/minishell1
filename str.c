/*
** append.c for mysh in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Jan  4 13:33:24 2017 Cédric Thomas
** Last update Wed Jan  4 21:03:15 2017 Cédric Thomas
*/
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "mysh.h"

int	my_nullstrlen(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i])
    {
      i += 1;
    }
  return (i);
}

char	*strappend(char *s1, char *s2, int freeit)
{
  char	*new;
  int	len;
  int	i;

  len = my_nullstrlen(s1) + my_nullstrlen(s2);
  i = 0;
  if (len == 0 || (new = malloc(sizeof(char) * (len + 1))) == NULL)
    return (NULL);
  new[len] = 0;
  while (i < len)
    {
      if (i < my_nullstrlen(s1))
	new[i] = s1[i];
      else
	new[i] = s2[i - my_nullstrlen(s1)];
      i += 1;
    } 
  if (freeit == 3 || freeit == 1)
    free(s1);
  if (freeit == 3 || freeit == 2)
    free(s2);
  return (new);
}
