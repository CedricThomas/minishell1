/*
** env.c for env.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Jan  4 16:06:24 2017 Cédric Thomas
** Last update Wed Jan  4 20:56:29 2017 Cédric Thomas
*/
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "mysh.h"

int	getkeyindex(char **ae, char *key)
{
  int	i;
  int	len;

  i = -1;
  if (!ae || !key)
    return (-1);
  len = my_strlen(key);
  while (ae[++i] && my_strncmp(key, ae[i], len));
  if (!ae[i])
    return (-1);
  return (i);
}

char	*getkey(char **ae, char *key, int dup)
{
  int	index;
  int	len;
  char	*keyvalue;

  if ((index =getkeyindex(ae, key)) < 0)
    return (NULL);
  len = my_strlen(key);
  if (dup)
    if ((keyvalue = my_strdup(ae[index] + len + 1)) == NULL)
      return (NULL);
    else
      return (keyvalue);
  return (ae[index] + len + 1);
}

int	changekey(char **ae, char *key, char *value, int freeit)
{
  int	i;
  int	lenkey;
  int	lenvalue;
  char	*newkey;

  i = -1;
  if (!ae || !key || !value)
    return (0);
  lenkey = my_strlen(key);
  lenvalue = my_strlen(value);
  while (ae[++i] && my_strncmp(key, ae[i], lenkey));
  if (!ae[i])
    return (0);
  newkey = strappend(key, "=", freeit);
  newkey = strappend(newkey, value, 1 + freeit * 2);
  free(ae[i]);
  ae[i] = newkey;
  if (freeit)
    {
      free(value);
      free(key);
    }
  return (1);
}

char	**deletekey(char **ae, char *key, int freeit)
{
  int	i;
  int	index;
  char	**dup;

  i = -1;
  if ((index = getkeyindex(ae, key)) < 0)
    return (ae);
  while (ae[++i]);
  if ((dup = malloc(sizeof(char *) * i)) == NULL)
    return (NULL);
  i = -1;
  while (ae[++i])
    {
      if (i < index)
	dup[i] = ae[i];
      else if (i > index)
	dup[i - 1] = ae[i];
      else
	free(ae[i]);
    }
  dup[i - 1] = 0;
  free(ae);
  if (freeit)
    free(key);
  return (dup);
}

char	**addkey(char **ae, char *key, char *value, int freeit)
{
  int	i;
  char	**dup;

  i = -1;
  while (ae[++i]);
  if ((dup = malloc(sizeof(char *) * (i + 2))) == NULL)
    return (NULL);
  i = -1;
  while (ae[++i])
    {
      dup[i] = ae[i];
    }
  free(ae);
  dup[i] = strappend(key, "=", freeit);
  dup[i] = strappend(dup[i], value, 1 + freeit * 2);
  dup[i + 1] = 0;
  return (dup);
}
