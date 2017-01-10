/*
** setenv.c for setenv.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Jan  9 22:22:17 2017 
** Last update Tue Jan 10 16:03:51 2017 
*/
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

unsigned int    setenvsh(t_info *info, int index)
{
  if (info->cmd[index].argc == 1 && info->cmd[index].argv)
    my_show_wordtab(info->env);
  else if (info->cmd[index].argc == 2)
    if (getkey(info->env, info->cmd[index].argv[1], 0) == NULL)
      info->env = addkey(info->env, info->cmd[index].argv[1], "", 0);
    else
      changekey(info->env, info->cmd[index].argv[1], "", 0);
  else if (info->cmd[index].argc == 3)
    if (getkey(info->env, info->cmd[index].argv[1], 0) == NULL)
      info->env = addkey(info->env, info->cmd[index].argv[1],
			 info->cmd[index].argv[2], 0);
    else
      changekey(info->env, info->cmd[index].argv[1],
		info->cmd[index].argv[2], 0);
  else
    {
      my_puterror("setenv: Too many arguments.\n");
      info->last = 1;
    }
  return (1);
}
