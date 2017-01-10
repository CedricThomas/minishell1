/*
** unsetenv.c for unsetenv.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Jan 10 11:10:28 2017 
** Last update Tue Jan 10 16:03:40 2017 
*/
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

unsigned int    unsetenvsh(t_info *info, int index)
{
  if (info->cmd[index].argc <= 1)
    {
      info->last = 1;
      my_puterror("unsetenv: Too few arguments.\n");
    }
  else
    info->env = deletekey(info->env, info->cmd[index].argv[1], 0);
  return (1);
}
