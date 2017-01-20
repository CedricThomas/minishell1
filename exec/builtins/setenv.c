/*
** setenv.c for setenv.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Jan  9 22:22:17 2017 
** Last update Tue Jan 17 17:58:03 2017 Cédric Thomas
*/
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

void	my_setenv(t_info *info, char *key, char *value)
{
  int	i;

  i = -1;
  while (key[++i])
    {
      if (i == 0 && !is_betw('A', key[i], 'Z') && !is_betw('a', key[i], 'z'))
      	{
      	  my_puterror("setenv: Variable name must begin with a letter.\n");
	  info->last = 1;
      	  return ;
      	}
      else if (!is_betw('A', key[i], 'Z') && !is_in(key[i], "_")
      	       && !is_betw('a', key[i], 'z') && !is_betw('0', key[i], '9'))
      	{
      	  my_puterror("setenv: Variable name must");
      	  my_puterror(" contain alphanumeric characters.\n");
	  info->last = 1;
      	  return ;
      	}
    }
  if (getkey(info->env, key, 0) == NULL)
    info->env = addkey(info->env, key, value, 0);
  else
    changekey(info->env, key, value, 0);
}

int    setenvsh(t_info *info, int index)
{
  info->last = 0;
  if (info->cmd[index].argc == 1 && info->cmd[index].argv)
    my_show_wordtab(info->env);
  else if (info->cmd[index].argc == 2)
    my_setenv(info, info->cmd[index].argv[1], "");
  else if (info->cmd[index].argc == 3)
    my_setenv(info, info->cmd[index].argv[1], info->cmd[index].argv[2]);
  else
    {
      my_puterror("setenv: Too many arguments.\n");
      info->last = 1;
    }
  return (0);
}
